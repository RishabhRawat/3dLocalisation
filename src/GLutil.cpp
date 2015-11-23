#include "GLutil.h"
#include <vector>
#include <iostream>

void utilCheckGLError(const char* id)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr<<"Error at: "<<id<<std::endl;
        switch(err)
		{
			case GL_INVALID_ENUM:
				std::cerr<<"ERROR: GL_INVALID_ENUM\n";
				break;
			case GL_INVALID_VALUE:
				std::cerr<<"ERROR: GL_INVALID_VALUE\n";
				break;
			case GL_INVALID_OPERATION:
				std::cerr<<"ERROR: GL_INVALID_OPERATION\n";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cerr<<"ERROR: GL_INVALID_FRAMEBUFFER_OPERATION\n";
				break;
			case GL_OUT_OF_MEMORY:
				std::cerr<<"ERROR: GL_OUT_OF_MEMORY\n";
				break;
			default:
				std::cerr<<"ERROR: You should not be getting this error... something is seriously wrong\n";
				break;
		}
    }
}
void utilCheckFBOError(GLenum target, const char* id)
{
	GLenum err;
	if((err = glCheckFramebufferStatus(target)) != GL_FRAMEBUFFER_COMPLETE) {
			std::cerr<<"Error at: "<<id<<std::endl;
        switch(err)
		{
			case  GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				std::cerr<<"ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n";
				break;
			case  GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				std::cerr<<"ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				std::cerr<<"ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				std::cerr<<"ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n";
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				std::cerr<<"ERROR: GL_FRAMEBUFFER_UNSUPPORTED\n";
				break;
			default:
				std::cerr<<"ERROR: You should not be getting this error... something is seriously wrong\n";
				break;
		}
    }
}