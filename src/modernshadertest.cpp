#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "shader.h"
#include "VoxelGrid.h"
#define VOXEL_INTERNAL_FORMAT GL_RGBA

using namespace cv;


Shader shader;
Mat image;
GLuint texID;
GLuint gVAO, gVBO;

GLfloat identityMat [] =
{
1.0f, 0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f,
0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int vaoID[1]; // Our Vertex Array Object      
unsigned int vboID[1]; // Our Vertex Buffer Object  
GLuint vbo_sq_texcoords;

void createSquare(void) {  
	glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    // Put the three triangle verticies into the VBO
    GLfloat vertexData[] = {
        //  X     Y     Z     U     V
         -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
         -0.5f,0.5f, 0.0f,  0.0f, 1.0f,
         0.5f,-0.5f, 0.0f,  1.0f, 0.0f,
         0.5f,0.5f, 0.0f,  1.0f, 1.0f,

    };
	
	
	GLint attrib = glGetAttribLocation(shader.shader_id, "Vertex");
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    // connect the xyz to the "vPosition" attribute of the vertex shader
	
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE,5*sizeof(GLfloat), NULL);

	attrib = glGetAttribLocation(shader.shader_id, "vertTexCoord");
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat),(const GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(attrib);


    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}  

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	image = imread("bb.jpg");
	if(!image.data)
		std::cout << "ERROR: could not load image" << std::endl;

	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, image.step/image.elemSize());
	
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	if(image.channels() == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
	else if(image.channels() == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
	
	
	
	GLenum errrr = glGetError();
	if(errrr!=GL_NO_ERROR)
		std::cout<<errrr;
	

	shader.init("shader.vert", "shader.frag");
	createSquare();
	
}

void display (void) {
	glEnable(GL_TEXTURE_2D);

	glClearColor (0.0,1.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shader.bind();
	
	glActiveTexture(GL_TEXTURE0 + 0);
	
	int TrasformMatrix = glGetUniformLocation(shader.shader_id, "Transform");
	glUniformMatrix4fv(TrasformMatrix,1,GL_FALSE,identityMat);
	
	int decalTexLocation = glGetUniformLocation(shader.shader_id, "my_color_texture");
	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(decalTexLocation, 0);
	
	glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0); // Unbind our Vertex Array Object
	
	shader.unbind();
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
		std::cout<<GL_NO_ERROR<<std::endl<<GL_INVALID_ENUM<<std::endl<<GL_INVALID_VALUE<<std::endl<<GL_INVALID_OPERATION<<std::endl<<GL_INVALID_FRAMEBUFFER_OPERATION<<std::endl<<GL_OUT_OF_MEMORY<<std::endl;
    }

	glutSwapBuffers();
}

void reshape (int width, int height) {
	if(width > height){		
		identityMat[0]= 1.0;//height/width;
		identityMat[5]= 1.0f;
	}
	else{
		identityMat[5]= 1.0;//height/width;
		identityMat[0]= 1.0f;
  	}
}

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //set up the double buffering
	//glutInitWindowSize(2,2);
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
