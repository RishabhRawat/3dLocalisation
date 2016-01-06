#include "GLutil.h"
#include <vector>
#include <iostream>

void glfwSetFPSinTitle(GLFWwindow *&window)
{
    // Measure speed
    double currentTime = glfwGetTime();
    static int nbFrames = 0;
    static double lastTime = 0;

    nbFrames++;

    if (currentTime - lastTime >= 1.0) { // If last cout was more than 1 sec ago
        char title[256];
        title[255] = '\0';

        snprintf(title, 255, "FPS: %d", nbFrames);

        glfwSetWindowTitle(window, title);

        nbFrames = 0;
        lastTime += 1.0;
    }
}

void glfw_error_callback(int error, const char* description)
{
    std::cout<<"ERROR: ";
    fputs(description, stderr);
    std::cout<<std::endl;
}

void openglCallbackFunction(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar* message,
                            const void* userParam)
{

    std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: " << message << std::endl;
    std::cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";
    switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
    exit(1);
}
