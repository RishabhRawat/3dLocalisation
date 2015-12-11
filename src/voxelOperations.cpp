#include "voxelOperations.h"
#include "GLutil.h"
#include <vector>
#include <iostream>

GLuint utilCreate3DVoxel(int size)
{
	std::vector<GLubyte> InitialData(size*size*size*4, 255);
	
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_3D, texID);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, size, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, &InitialData[0]);
	
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glBindTexture(GL_TEXTURE_3D, 0);
	return texID;
	
}

// Read from ping write to pong
void updateVoxel(GLuint FramebufferName, GLuint gVAO, GLuint Voxel)
{
	glViewport(0,0,VOXELNUM,VOXELNUM);	
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	shader.bind();
	
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_3D, Voxel);
	
	glUniform1i(shader.shaderUniform("my_color_texture"), 0);
	glUniformMatrix4fv(shader.shaderUniform("Transform"),1,GL_FALSE,identityMat);
	
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	
	glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0); // Unbind our Vertex Array Object
	utilCheckGLError("3");

	
	shader.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

