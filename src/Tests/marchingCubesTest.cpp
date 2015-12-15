#include <iostream>
#include "voxelOperations.h"
#include "marchingCubes.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>  


#define VOXEL_INTERNAL_FORMAT GL_RGBA

Shader shader;
glm::mat4 MVP;
glm::mat4 Projection, View, Model;

GLuint texID[1];
GLuint lookupTableTexture;

GLuint gVAO, gVBO;

void createSquare(void)
{
	glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
	// make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
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
	GLint attrib = glGetAttribLocation(shader.shader_id, "Vertex");
    glEnableVertexAttribArray(attrib);
	
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_TRUE,3*sizeof(GLfloat), NULL);
	
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
	
	
	InitialData[(16+5)*4] = 1;
	InitialData[(16+6)*4] = 1;
	
	InitialData[(16+9)*4] = 1;
	InitialData[(16+10)*4] = 1;
	
	InitialData[(16*2+5)*4] = 1;
	InitialData[(16*2+6)*4] = 1;
	
	InitialData[(16*2+9)*4] = 1;
	InitialData[(16*2+10)*4] = 1;
	
    texID[0] = utilCreate3DVoxelFromData(VOXELNUM,InitialData);
    const char* Vshader = "#version 440 \n in vec3 Vertex;\nvoid "
                          "main() {	\n	gl_Position = vec4(Vertex,1.0);\n}";
    const char* Gshader = textFileRead("simpleG.geo");
    //const char* Gshader = textFileRead("error2.geo");

	const char* Fshader = textFileRead("simpleFshader.frag");
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
	
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, texID[0]);
    glUniform1i(shader.shaderUniform("my_color_texture"), 0);
    glUniform1i(shader.shaderUniform("my_data_texture"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lookupTableTexture);
	glUniform1i(shader.shaderUniform("lookupTableTexture"), 1);
	
    glUniformMatrix4fv(shader.shaderUniform("Transform"), 1, GL_FALSE, glm::value_ptr(MVP));
    glBindVertexArray(gVAO);
    glDrawArrays(GL_POINTS, 0, 27);
    glBindVertexArray(0); // Unbind our Vertex Array Object
    
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
bool sticky, drag;
double oldx, oldy;
double dx, dy;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		sticky = true;
		drag = true;
		dx = 0;
		dy = 0;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		sticky = false;
		if(dx != 0 && dy != 0)
		{
			float leng = std::sqrt(dx*dx+dy*dy)/300.0f;
			Model = glm::rotate(Model, leng, glm::normalize(glm::vec3(dy, dx, 0.0f)));
			MVP = Projection * View * Model;
			dx = 0;
			dy = 0;
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(yoffset > 0)
		Model = glm::scale(Model, glm::vec3(0.9f));
	else
		Model = glm::scale(Model, glm::vec3(1/0.9f));
	MVP = Projection * View * Model;
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(drag)
	{
		oldx = xpos;
		oldy = ypos;
		drag = false;
	}
	if(sticky)
	{
		dx = xpos-oldx;
		dy = ypos-oldy;
		if(dx*dy == 0)
			return;
		float leng = std::sqrt(dx*dx+dy*dy)/300.0f;
		
		MVP = Projection * View * glm::rotate(Model, leng, glm::normalize(glm::vec3(dy, dx, 0.0f)));
	}
}





static void openglCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar* message,
                                     const void* userParam)
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
	exit(1);
}

void glfw_error_callback(int error, const char* description)
{
	std::cerr<<"sssssssssssssssssssss";
	std::cout<<"sssssssssssssssssssss";
    fputs(description, stderr);
}

int main(int argc, char** argv)
{
	
	Model = glm::mat4();;
	View = glm::mat4();
	Projection = glm::mat4();;

	if (!glfwInit())
    exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE );
	glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);
	
	glfwSetErrorCallback(glfw_error_callback);
	
	GLFWwindow* window = glfwCreateWindow(500, 500, "My Title", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	
	
	glfwSwapInterval(1);
	 
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
	
	
	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, NULL);
	GLuint unusedIds = 0;
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
	
	init();
	
	int nbFrames;
	double currentTime = 0;
	double lastTime = 0;
	while (!glfwWindowShouldClose(window)){
	    display();

	    // Measure speed
	    double currentTime = glfwGetTime();
	    nbFrames++;

	    if (currentTime - lastTime >= 1.0) { // If last cout was more than 1 sec ago
	        char title[256];
	        title[255] = '\0';

	        snprintf(title, 255, "FPS: %d", nbFrames);

	        glfwSetWindowTitle(window, title);

	        nbFrames = 0;
	        lastTime += 1.0;
	    }

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

