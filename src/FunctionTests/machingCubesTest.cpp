#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "../GLutil.h"
#include "../voxelOperations.h"
#define VOXEL_INTERNAL_FORMAT GL_RGBA

using namespace cv;
Shader shader;



GLfloat viewMat [16] =
{
0.5f, 0.0f, 0.0f, 0.0f,
0.0f, 0.5f, 0.0f, 0.0f,
0.0f, 0.0f, 0.5f, 0.0f,
0.2f, 0.2f, 0.0f, 1.0f 		// X Y Z 1	 culled from -1 to 1
};

Mat image;
GLuint texID[1];

GLuint gVAO, gVBO;

void createSquare(void) {  
glGenVertexArrays(1, &gVAO);

    glBindVertexArray(gVAO);
    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    // Put the three triangle verticies into the VBO
    GLfloat vertexData[] = {
		//X		Y		Z		S	T		P
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f


    };
	
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
   
	glEnableVertexAttribArray(shader.shaderAttrib("Vertex"));
    glVertexAttribPointer(shader.shaderAttrib("Vertex"), 3, GL_FLOAT, GL_FALSE,6*sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(shader.shaderAttrib("vertTexCoord"));
	glVertexAttribPointer(shader.shaderAttrib("vertTexCoord"), 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat),(const GLvoid*)(3*sizeof(GLfloat)));
    

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}  

void init(void) {

	//shader = new Shader();
	//PING PONG BUFFERS
	texID[0] = utilCreate3DVoxel(VOXELNUM); 

	shader.init("shader.vert", "shader.frag");
	createSquare();	
	utilCheckGLError("init");
}

void display (void) {
	
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT);

//glViewport(0,0,VOXELNUM,VOXELNUM);	
	shader.bind();
	
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_3D, texID[0]);
	
	glUniform1i(shader.shaderUniform("my_color_texture"), 0);
	glUniformMatrix4fv(shader.shaderUniform("Transform"),1,GL_FALSE,viewMat);
	
	glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0); // Unbind our Vertex Array Object
	utilCheckGLError("3");

	
	shader.unbind();


	glutSwapBuffers();

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
