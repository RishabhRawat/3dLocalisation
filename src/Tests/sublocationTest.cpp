#include <iostream>
#include "voxelOperations.h"
#include "marchingCubes.h"
#include "voxel.h"
#include "GLutil.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext.hpp>

#define CLIP_D 0.03f
#define VOXEL_INTERNAL_FORMAT GL_RGBA

Shader shader_cube;
Shader shader_texture;

glm::mat4 MVP;
glm::mat4 Projection, View, Model;
glm::mat3 K_camera, invK;

GLuint texID[2];
GLuint lookupTableTexture;
GLuint incomingImage;
GLuint FramebufferName;

GLuint gVAO[2], gVBO[2];

Voxel pngObject;


void createSquare(void)
{
    glGenVertexArrays(2, gVAO);
    glBindVertexArray(gVAO[0]);
    // make and bind the VBO
    glGenBuffers(2, gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO[0]);
    // Put the three triangle verticies into the VBO

    GLfloat vertexData[] = {   -1, -1, 0, 0, 0,
                               +1, -1, 0, 1, 0,
                               -1, +1, 0, 0, 1,
                               +1, +1, 0, 1, 1};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vPosition" attribute of the vertex shader
    GLint attrib = glGetAttribLocation(shader_texture.shader_id, "Vertex");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_TRUE,5*sizeof(GLfloat), NULL);

    attrib = glGetAttribLocation(shader_texture.shader_id, "TexCoord_in");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_TRUE,5*sizeof(GLfloat), (const GLvoid*)(3*sizeof(GLfloat)));

    glBindVertexArray(gVAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO[1]);

    GLfloat cubeData[] = { -1, -1,  1,
                           +1, -1,  1,
                           +1, +1,  1,
                           -1, +1,  1,

                           -1, -1, -1,
                           +1, -1, -1,
                           +1, +1, -1,
                           -1, +1, -1,

                           -1, -1,  1,
                           -1, -1, -1,

                           +1, -1,  1,
                           +1, -1, -1,

                           +1, +1,  1,
                           +1, +1, -1,

                           -1, +1,  1,
                           -1, +1, -1};

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData), cubeData, GL_STATIC_DRAW);


    attrib = glGetAttribLocation(shader_cube.shader_id, "Vertex");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_TRUE, 3*sizeof(GLfloat),NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void init(void)
{

    const char* Vshader_render = textFileRead("textureMap.vert");

    const char* Fshader_render = textFileRead("textureMap.frag");
    shader_texture.init(Vshader_render, Fshader_render, 0);



    glGenTextures(1, &incomingImage);
    glBindTexture(GL_TEXTURE_2D, incomingImage);
    glTexImage2D(GL_TEXTURE_2D, 0,  GL_R16F , pngObject.width, pngObject.height, 0,   GL_RED,  GL_UNSIGNED_SHORT, &pngObject.depthMap[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    const char* Vshader_cube = textFileRead("renderShape.vert");
    const char* Fshader_cube = textFileRead("passThrough.frag");

    shader_cube.init(Vshader_cube, Fshader_cube, 0);


    createSquare();

    K_camera = glm::mat3(535.4, 0, 320.1, 0, 539.2, 247.6, 0, 0, 1);
    invK = glm::inverse(K_camera);
}
GLfloat scale = 0;
glm::quat base(0, 0, 0, 0);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        scale += 0.01;
        std::cout<<scale<<std::endl;
    }
    if (key == GLFW_KEY_R && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        scale -= 0.01;
        std::cout<<scale<<std::endl;
    }
    if (key == GLFW_KEY_X && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        base.x += 0.01;
        std::cout<<base.x<<std::endl;
    }
    if (key == GLFW_KEY_Y && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        base.y += 0.01;
        std::cout<<base.y<<std::endl;
    }
    if (key == GLFW_KEY_Z && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        base.z += 0.01;
        std::cout<<base.z<<std::endl;
    }
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        base.w += 0.01;
        std::cout<<base.w<<std::endl;
    }
}


void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);


    {
        glViewport(0,0,640,480);
        shader_texture.bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, incomingImage);

        glUniform1i(shader_texture.shaderUniform("backgroundImage"), 0);

        //glUniformMatrix4fv(shader_rendering.shaderUniform("Transform"), 1, GL_FALSE, glm::value_ptr(MVP));
        glBindVertexArray(gVAO[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0); // Unbind our Vertex Array Object

        shader_texture.unbind();


        shader_cube.bind();

        glUniform1f(shader_cube.shaderUniform("scale"),scale);
        glUniform3f(shader_cube.shaderUniform("alterPosition"),0,0,0);
        glm::quat q(0.1843-base.x, -0.2495-base.y, 0.7955-base.z, -0.5204-base.w);
        glm::mat3 Rmat = glm::mat3_cast(q);
        Rmat = glm::inverse(Rmat);

        glUniform3f(shader_cube.shaderUniform("t_gk"),-2.1510, 0.6848, 1.4888);
        glUniformMatrix3fv(shader_cube.shaderUniform("invR"),1,GL_FALSE,&Rmat[0][0]);
        glUniformMatrix3fv(shader_cube.shaderUniform("K_camera"),1,GL_TRUE,&K_camera[0][0]);
        //glUniformMatrix3fv(shader_cube.shaderUniform("InverseK"),1,GL_TRUE,&invK[0][0]);


        glBindVertexArray(gVAO[1]);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glDrawArrays(GL_LINE_LOOP, 4, 4);

        glDrawArrays(GL_LINES, 8, 2);
        glDrawArrays(GL_LINES, 10, 2);
        glDrawArrays(GL_LINES, 12, 2);
        glDrawArrays(GL_LINES, 14, 2);

        GLuint sideV[2] = {0,4};
        glDrawElements(GL_LINE_STRIP,2,GL_UNSIGNED_INT,sideV);

        glBindVertexArray(0); // Unbind our Vertex Array Object


        shader_cube.unbind();

    }
}


int main(int argc, char** argv)
{

    Model = glm::mat4();;
    View = glm::mat4();
    Projection = glm::mat4();;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE );
    glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(glfw_error_callback);

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glfwSwapInterval(0);

    pngObject.readPngDepthMap("1341841873.505863.png");

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }


    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openglCallbackFunction, NULL);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);

    init();

    while (!glfwWindowShouldClose(window)){
        display();

        glfwSetFPSinTitle(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

