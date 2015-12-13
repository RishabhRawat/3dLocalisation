#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "GLutil.h"
#include "voxelOperations.h"
#include "marchingCubes.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>  


#define VOXEL_INTERNAL_FORMAT GL_RGBA

using namespace cv;
Shader shader;
glm::mat4 MVP;
glm::mat4 Projection, View, Model;

Mat image;
GLuint texID[1];
GLuint lookupTableTexture;

GLuint gVAO, gVBO;

void createSquare(void)
{
	utilCheckGLError("q");
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
	utilCheckGLError("c");
    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	utilCheckGLError("b");
    // Put the three triangle verticies into the VBO
    GLfloat vertexData[(VOXELNUM-1)*(VOXELNUM-1)*(VOXELNUM-1)*3];

    for (unsigned int z = 0; z < 3; z++) {
		for (unsigned int y = 0; y < 3; y++) {
			for (unsigned int x = 0; x < 3; x++) {
				vertexData[(x+3*y+z*9)*3] = (float)x;
				vertexData[(x+3*y+z*9)*3+1] = (float)y;
				vertexData[(x+3*y+z*9)*3+2] = (float)z;
			}
		}
    }
	

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    // connect the xyz to the "vPosition" attribute of the vertex shader
	utilCheckGLError("a");
	GLint attrib = glGetAttribLocation(shader.shader_id, "Vertex");
    glEnableVertexAttribArray(attrib);
	
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_TRUE,3*sizeof(GLfloat), NULL);
	utilCheckGLError("s");

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}  

void init(void)
{
    // shader = new Shader();
	//assuming VOXELNUM = 4
	glGenTextures(1, &lookupTableTexture);
	glBindTexture(GL_TEXTURE_2D, lookupTableTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8I, 16, 256, 0,  GL_RED_INTEGER, GL_BYTE, &triTable[0][0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	
	
	std::vector<GLubyte> InitialData(VOXELNUM*VOXELNUM*VOXELNUM*4, 0);
	
	
	InitialData[(16+5)*4] = 1.0f;
	InitialData[(16+6)*4] = 1.0f;
	
	InitialData[(16+9)*4] = 1.0f;
	InitialData[(16+10)*4] = 1.0f;
	
	InitialData[(16*2+5)*4] = 1.0f;
	InitialData[(16*2+6)*4] = 1.0f;
	
	InitialData[(16*2+9)*4] = 1.0f;
	InitialData[(16*2+10)*4] = 1.0f;
	
    texID[0] = utilCreate3DVoxelFromData(VOXELNUM,InitialData);
    const char* Vshader = "#version 330 \n in vec3 Vertex;\nvoid "
                          "main() {	\n	gl_Position = vec4(Vertex,1.0);\n}";
    const char* Gshader = textFileRead("simpleG.geo");
	const char* Fshader = "#version 330 \n uniform sampler3D my_color_texture;\n in vec4 fragColor;\n out vec4 out_Color;\n    void "
                          "main()\n    {\n	out_Color = fragColor;\n    }\n";
    shader.init(Vshader, Fshader, Gshader, 0);
	createSquare();
}

void display(void)
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // glViewport(0,0,VOXELNUM,VOXELNUM);
    shader.bind();
	
	glUniform4fv(shader.shaderUniform("cubeVector"), 8*4,&cubeVector[0][0]);
	
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_3D, texID[0]);
    glUniform1i(shader.shaderUniform("my_color_texture"), 0);
    glUniform1i(shader.shaderUniform("my_data_texture"), 0);
	
	glBindTexture(GL_TEXTURE_2D, lookupTableTexture);
	glUniform1i(shader.shaderUniform("lookupTableTexture"), 0);
	
    glUniformMatrix4fv(shader.shaderUniform("Transform"), 1, GL_FALSE, glm::value_ptr(MVP));
    glBindVertexArray(gVAO);
    glDrawArrays(GL_POINTS, 0, 27);
    glBindVertexArray(0); // Unbind our Vertex Array Object
    utilCheckGLError("3");

    shader.unbind();
}

void reshape(int width, int height)
{
    /*
    if(width > height){
            identityMat[0]= 1.0;//height/width;
            identityMat[5]= 1.0f;
    }
    else{
            identityMat[5]= 1.0;//height/width;
            identityMat[0]= 1.0f;
    }*/
}
/*
float oldx, oldy, drag;
void mouseHandler(int button, int state, int x, int y)
{
	if (button == 3) // It's a wheel up event
    {
		// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_UP)
			return; // Disregard redundant GLUT_UP events
		Model = glm::scale(Model, glm::vec3(0.9f));
    } else if (button == 4) // It's a wheel down event
    {
		// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_UP)
			return; // Disregard redundant GLUT_UP events
		Model = glm::scale(Model, glm::vec3(1/0.9f));
    } else if (button == GLUT_LEFT_BUTTON) // It's a wheel down event
    {
		// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_DOWN && drag == 0){
			oldx = x;
			oldy = y;
			drag = 1;
			
		}
		float dx = x-oldx;
		float dy = y-oldy;
		if(dx*dy == 0)
			return;
		Model = glm::rotate(Model, sqrt(dx*dx+dy*dy)/300.0f, glm::normalize(glm::vec3(dy, dx, 0.0f)));
		drag = 0;
    } else { // normal button event
		printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    }
    MVP = Projection * View * Model;
}
void dragHandler(int x, int y)
{
	if(drag)
	{
		float dx = x-oldx;
		float dy = y-oldy;
		if(dx*dy == 0)
			return;
		MVP = Projection * View * glm::rotate(Model, sqrt(dx*dx+dy*dy)/300.0f, glm::normalize(glm::vec3(dy, dx, 0.0f)));
	}
}*/
/*
void APIENTRY openglCallbackFunction(GLenum source,
GLenum type,
GLuint id,
GLenum severity,
GLsizei length,
const GLchar* message,
void * userParam)
{
printf("Debug message with source 0x%04X, type 0x%04X, "
"id %u, severity 0x%0X, '%s'\n",
source, type, id, severity, message);
}*/

static void openglCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar* message,
                                     void* userParam)
{

    std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: " << message << std::endl;
    std::cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
	std::cout << "ERROR";
	break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
	std::cout << "DEPRECATED_BEHAVIOR";
	break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
	std::cout << "UNDEFINED_BEHAVIOR";
	break;
    case GL_DEBUG_TYPE_PORTABILITY:
	std::cout << "PORTABILITY";
	break;
    case GL_DEBUG_TYPE_PERFORMANCE:
	std::cout << "PERFORMANCE";
	break;
    case GL_DEBUG_TYPE_OTHER:
	std::cout << "OTHER";
	break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";
    switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
	std::cout << "LOW";
	break;
    case GL_DEBUG_SEVERITY_MEDIUM:
	std::cout << "MEDIUM";
	break;
    case GL_DEBUG_SEVERITY_HIGH:
	std::cout << "HIGH";
	break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}
void glfw_error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(int argc, char** argv)
{
	
	Model = glm::mat4();;
	View = glm::mat4();
	Projection = glm::mat4();;

	if (!glfwInit())
    exit(EXIT_FAILURE);
	
	init();
	glfwSetErrorCallback(glfw_error_callback);
	
	GLFWwindow* window = glfwCreateWindow(500, 500, "My Title", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// remember

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	/*
    glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	/////
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG );
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, NULL);
	GLuint unusedIds = 0;
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
	////

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // set up the double buffering
	
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A basic OpenGL Window");
	
	
	glutMotionFunc(dragHandler);
    glutMouseFunc(mouseHandler);
	
    glutDisplayFunc(display);
    glutIdleFunc(display);

	

    glutReshapeFunc(reshape);

    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	printf("glewInit failed");
	utilCheckGLError("t");
    
    if (!GLEW_VERSION_4_4) // check that the machine supports the 2.1 API.
	exit(1);           // or handle the error in a nicer way

    glutMainLoop();
	*/
	while (!glfwWindowShouldClose(window)){
		display();
		glfwSwapBuffers(window);

	}
	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

