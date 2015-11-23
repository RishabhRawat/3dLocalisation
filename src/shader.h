#ifndef __SHADER_H
#define __SHADER_H

#include <stdlib.h>
#include <cstdio>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include <string>

class Shader {
	public:
		Shader();
		Shader(const char *vsFile, const char *fsFile);
		~Shader();

		void init(const char *vsFile, const char *fsFile);

		void bind();
		void unbind();
		void CompileShader(unsigned int shader);
		GLint shaderUniform(const char* name);
		GLint shaderAttrib(const char* name);

		unsigned int id();

	public:
		unsigned int shader_id;
		unsigned int shader_vp;
		unsigned int shader_fp;
};

#endif