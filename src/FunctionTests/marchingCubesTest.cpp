#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "../GLutil.h"
#include "../voxelOperations.h"

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
				vertexData[(x+4*y+z*16)*3] = (float)x;
				vertexData[(x+4*y+z*16)*3+1] = (float)y;
				vertexData[(x+4*y+z*16)*3+2] = (float)z;
			}
		}
    }
	

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    // connect the xyz to the "vPosition" attribute of the vertex shader

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
	std::vector<GLubyte> InitialData(VOXELNUM*VOXELNUM*VOXELNUM*4, 0);
	
	InitialData[(16+1)*4] = 1.0f;
	InitialData[(16+2)*4] = 1.0f;
	InitialData[(16+4)*4] = 1.0f;
	InitialData[(16+5)*4] = 1.0f;
	InitialData[(16+6)*4] = 1.0f;
	InitialData[(16+7)*4] = 1.0f;
	InitialData[(16+8)*4] = 1.0f;
	InitialData[(16+9)*4] = 1.0f;
	InitialData[(16+10)*4] = 1.0f;
	InitialData[(16+11)*4] = 1.0f;
	InitialData[(16+13)*4] = 1.0f;
	InitialData[(16+14)*4] = 1.0f;
	
	InitialData[(16*2+1)*4] = 1.0f;
	InitialData[(16*2+2)*4] = 1.0f;
	InitialData[(16*2+4)*4] = 1.0f;
	InitialData[(16*2+5)*4] = 1.0f;
	InitialData[(16*2+6)*4] = 1.0f;
	InitialData[(16*2+7)*4] = 1.0f;
	InitialData[(16*2+8)*4] = 1.0f;
	InitialData[(16*2+9)*4] = 1.0f;
	InitialData[(16*2+10)*4] = 1.0f;
	InitialData[(16*2+11)*4] = 1.0f;
	InitialData[(16*2+13)*4] = 1.0f;
	InitialData[(16*2+14)*4] = 1.0f;
	
    texID[0] = utilCreate3DVoxelFromData(VOXELNUM,InitialData);
    const char* Vshader = "#version 330 \n in vec3 Vertex;\nvoid "
                          "main() {	\n	gl_Position = vec4(Vertex,1.0);\n}";
    const char* Gshader = textFileRead("simpleG.geo");
	const char* Fshader = "#version 330 \n uniform sampler3D my_color_texture;\n out vec4 out_Color;\n    void "
                          "main()\n    {\n	out_Color = vec4(1.0f,1.0f,1.0f,1.0f);\n    }\n";
    shader.init(Vshader, Fshader, Gshader, 0);
    createSquare();
	std::cout<<"initCOmplete"<<std::endl;
}

void display(void)
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	std::cout<<"initCOmplete"<<std::endl;
    // glViewport(0,0,VOXELNUM,VOXELNUM);
    shader.bind();
	std::cout<<"initCOmplete"<<std::endl;
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_3D, texID[0]);

    glUniform1i(shader.shaderUniform("my_color_texture"), 0);
    glUniform1i(shader.shaderUniform("my_data_texture"), 0);
    glUniformMatrix4fv(shader.shaderUniform("Transform"), 1, GL_FALSE, glm::value_ptr(MVP));
	std::cout<<"initCOmplete"<<std::endl;
    glBindVertexArray(gVAO);
    glDrawArrays(GL_POINTS, 0, 64);
    glBindVertexArray(0); // Unbind our Vertex Array Object
    utilCheckGLError("3");

    shader.unbind();

    glutSwapBuffers();
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
}
int main(int argc, char** argv)
{
	
	Model = glm::mat4();;
	View = glm::mat4();
	Projection = glm::mat4();;


    glutInit(&argc, argv);
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
    if (!GLEW_VERSION_3_3) // check that the machine supports the 2.1 API.
	exit(1);           // or handle the error in a nicer way
    init();

    glutMainLoop();

    return 0;
}
