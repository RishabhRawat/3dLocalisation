#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "shader.h"

using namespace cv;


Shader shader;
Mat image;
GLuint texID;

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	image = imread("bb.jpg");
	if(!image.data)
		std::cout << "ERROR: could not load image" << std::endl;
                
	// initialze OpenGL texture             
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, image.step/image.elemSize());
	
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texID);
	
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	if(image.channels() == 3)
			glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
	else if(image.channels() == 4)
			glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.data);


	shader.init("shader.vert", "shader.frag");
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); 
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	
}

void display (void) {
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	//	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	shader.bind();
	
	int decalTexLocation = glGetUniformLocation(shader.shader_id, "my_color_texture");
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texID);
	glUniform1i(decalTexLocation, 0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor4f(1.0,0.0,1.0,1.0);
		glTexCoord2i(0,image.rows);
		glVertex3f(-1.0,-1.0, 0.0);
		glTexCoord2i(image.cols,image.rows);
		glVertex3f(1.0,-1.0,0.0);
		glTexCoord2i(image.cols,0);
		glVertex3f(1.0,1.0, 0.0);
		glTexCoord2i(0,0);
		glVertex3f(-1.0,1.0, 0.0);
	glEnd();
//	cube();
	shader.unbind();
	
	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }

	glutSwapBuffers();
}

void reshape (int width, int height) {
	 // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   if (width >= height) {
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
   glMatrixMode(GL_MODELVIEW);
  	
}

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //set up the double buffering
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A basic OpenGL Window");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(reshape);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
		printf("glewInit failed");
	init();

	glutMainLoop();

	return 0;
}
