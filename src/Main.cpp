#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "GLutil.h"
#include "voxelOperations.h"
#define VOXEL_INTERNAL_FORMAT GL_RGBA

using namespace cv;
Shader shader;


Mat image;
GLuint texID[2];
GLuint ping;

GLuint FramebufferName[2];
GLuint gVAO, gVBO;

void createSquare(void) {  
glGenVertexArrays(1, &gVAO);

    glBindVertexArray(gVAO);
    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    // Put the three triangle verticies into the VBO
    GLfloat vertexData[] = {
        //  X     Y     Z     U     V
         -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         -1.0f,1.0f, 0.0f,  0.0f, 1.0f,
         1.0f,-1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,1.0f, 0.0f,  1.0f, 1.0f,

    };
	
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
   
	glEnableVertexAttribArray(shader.shaderAttrib("Vertex"));
    glVertexAttribPointer(shader.shaderAttrib("Vertex"), 3, GL_FLOAT, GL_FALSE,5*sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(shader.shaderAttrib("vertTexCoord"));
	glVertexAttribPointer(shader.shaderAttrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat),(const GLvoid*)(3*sizeof(GLfloat)));
    

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}  

void init(void) {

	//shader = new Shader();
	//PING PONG BUFFERS
	texID[0] = utilCreate3DVoxel(VOXELNUM); 
	texID[1] = utilCreate3DVoxel(VOXELNUM);
	glGenFramebuffers(2, FramebufferName);
	ping = 1;
	
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName[0]);
	glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, texID[0], 0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName[1]);
	glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, texID[1], 0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shader.init("shader.vert", "shader.frag");
	createSquare();	
	utilCheckGLError("init");
}

void display (void) {
	
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	std::cout<<"going to write in: "<<1-ping<<std::endl;
	updateVoxel(FramebufferName[1-ping],gVAO,texID[ping]);
	utilCheckGLError("display");
	glutSwapBuffers();
	ping = 1-ping;
}

void reshape (int width, int height) {
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

int main (int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //set up the double buffering
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A basic OpenGL Window");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(reshape);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
		printf("glewInit failed");
	if (!GLEW_VERSION_3_3)  // check that the machine supports the 2.1 API.
		exit(1); // or handle the error in a nicer way
	init();

	glutMainLoop();

	return 0;
}
