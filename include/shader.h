#ifndef __SHADER_H
#define __SHADER_H

#include <stdlib.h>
#include <cstdio>
/*
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glut.h>
*/
#include "glad/glad.h"
//#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include <string>

char* textFileRead(const char *fileName);

class Shader {
	public:
		Shader();
		Shader(const char *vsFile, const char *fsFile);
		~Shader();

		void init(const char *vsFile, const char *fsFile);
		void init(const char *vsFile, const char *fsFile, const char *gsFile);
		void init(const char *vsText, const char *fsText, int textFlag);
		void init(const char *vsText, const char *fsText, const char *gsText, int textFlag);

		void bind();
		void unbind();
		static void CompileShader(unsigned int shader);
		static unsigned int addShader(const char * shaderFileName, GLenum shaderType);
		static unsigned int addShaderfromText(const char * Text, GLenum shaderType);
		GLint shaderUniform(const char* name);
		GLint shaderAttrib(const char* name);

		unsigned int id();

	public:
		unsigned int shader_id;
		unsigned int shader_vp;
		unsigned int shader_fp;
		unsigned int shader_gp;
};

#endif