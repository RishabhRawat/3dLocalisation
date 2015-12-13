#include "Common.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "shader.h"
//#include "VoxelGrid.h"
#include "voxelOperations.h"
#include "GLutil.h"
#define VOXEL_INTERNAL_FORMAT GL_RGBA

using namespace cv;


Shader shader;
Mat image;
GLuint texID_1, texID_2;
GLuint FramebufferName;
GLuint gVAO, gVBO;
/*
GLfloat identityMat [] =
{
1.0f, 0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f,
0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f
};
*/

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
	
	
	GLint attrib = glGetAttribLocation(shader.shader_id, "Vertex");
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
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

	//PING PONG BUFFERS
	texID_1 = utilCreate3DVoxel(VOXELNUM); 
	texID_2 = utilCreate3DVoxel(VOXELNUM);
	
	glGenFramebuffers(1, &FramebufferName);
	
	utilCheckGLError("init");

	shader.init("shader.vert", "shader.frag");
	createSquare();	
}

void display (void) {
	
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0,0,VOXELNUM,VOXELNUM);	
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	shader.bind();
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_3D, texID_2);
	glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, texID_2, 0, 0);
	
	int decalTexLocation = glGetUniformLocation(shader.shader_id, "my_color_texture");
	glBindTexture(GL_TEXTURE_3D, texID_1);
	glUniform1i(decalTexLocation, 0);
	
	
	int TrasformMatrix = glGetUniformLocation(shader.shader_id, "Transform");
	glUniformMatrix4fv(TrasformMatrix,1,GL_FALSE,identityMat);
	
	glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0); // Unbind our Vertex Array Object
	
	GLenum attachment  = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &attachment);
	
	shader.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	utilCheckGLError("display");
	glutSwapBuffers();
}

void reshape (int width, int height) {/*
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
