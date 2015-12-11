#include "shader.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

char* textFileRead(const char *fileName) {
	char* text;
    
	if (fileName) {
        FILE *file = fopen(fileName, "rt");
        
		if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
			if (count > 0) {
				text = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
	}
	return text;
}

Shader::Shader() {
    
}

Shader::Shader(const char *vsFile, const char *fsFile) {
    init(vsFile, fsFile);
}

void Shader::init(const char *vsFile, const char *fsFile) {
	shader_vp = addShader(vsFile,GL_VERTEX_SHADER);
	shader_fp = addShader(fsFile,GL_FRAGMENT_SHADER);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
}

void Shader::init(const char *vsFile, const char *fsFile, const char *gsFile) {
	shader_vp = addShader(vsFile,GL_VERTEX_SHADER);
	shader_fp = addShader(fsFile,GL_FRAGMENT_SHADER);
	shader_gp = addShader(gsFile,GL_GEOMETRY_SHADER);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_gp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
}

void Shader::init(const char *vsText, const char *fsText, int textFlag) {
	shader_vp = addShaderfromText(vsText,GL_VERTEX_SHADER);
	shader_fp = addShaderfromText(fsText,GL_FRAGMENT_SHADER);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
}

void Shader::init(const char *vsText, const char *fsText, const char *gsText, int textFlag) {
	shader_vp = addShaderfromText(vsText,GL_VERTEX_SHADER);
	shader_gp = addShaderfromText(gsText,GL_GEOMETRY_SHADER);
	shader_fp = addShaderfromText(fsText,GL_FRAGMENT_SHADER);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_gp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
}

unsigned int Shader::addShader(const char * shaderFileName, GLenum shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	const char* Text = textFileRead(shaderFileName);
	if (!shader) {
        cout << "Shader file not found." << endl;
        exit(-1);
		return 9999;
    }
	glShaderSource(shader, 1, &Text, 0);
	Shader::CompileShader(shader);
	return shader;
}

unsigned int Shader::addShaderfromText(const char * Text, GLenum shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	if (!shader) {
        cout << "Shader file not found." << endl;
        exit(-1);
		return 9999;
    }
	glShaderSource(shader, 1, &Text, 0);
	Shader::CompileShader(shader);
	return shader;
}

Shader::~Shader() {
	cout<<"IN TROUBLE"<<endl;
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);
    
	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);
}

unsigned int Shader::id() {
	return shader_id;
}

void Shader::bind() {
	glUseProgram(shader_id);
}

void Shader::unbind() {
	glUseProgram(0);
}

GLint Shader::shaderUniform(const char* name){
	return glGetUniformLocation(shader_id, name);
}
GLint Shader::shaderAttrib(const char* name){
	return glGetAttribLocation(shader_id, name);
}

void Shader::CompileShader(unsigned int shader){
	glCompileShader(shader);
	GLint isCompiled = 0;
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		cout<<maxLength;
        std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
	    std::cout << string(infoLog.begin(), infoLog.end()) << std::endl;
		
		glDeleteShader(shader); // Don't leak the shader.
		exit(-1);
	}
    
}