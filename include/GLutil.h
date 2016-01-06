#ifndef GLUTIL_H
#define GLUTIL_H
#include "Common.h"

void glfwSetFPSinTitle(GLFWwindow *&window);

void openglCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar* message,
                                     const void* userParam);

void glfw_error_callback(int error, const char* description);


#endif // GLUTIL_H
