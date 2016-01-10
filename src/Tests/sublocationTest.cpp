#include <iostream>
#include "voxelOperations.h"
#include "marchingCubes.h"
#include "voxel.h"
#include "GLutil.h"
#include "filereader.h"


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
fileReader qdata, imageFiles;

glm::mat4 MVP;
glm::mat4 Projection, View, Model;
glm::mat4 K_camera, invK;
//float pos[3] = {-2.51, 1.248, 2.79};

float pos[3] = {2.43, 5, 3.68 };


GLfloat scale = .3;
//glm::quat base(1.0f, 0.08f, 0.02f, 0.25f);
glm::quat base(1.0f, 0.0f, 0.0f, 0.0f);
int play = 1;



GLuint texID[2];
GLuint lookupTableTexture;
GLuint incomingImage;
GLuint FramebufferName;

GLuint gVAO[2], gVBO[2];

Voxel pngObject;
int frame = 0;
int locframe = 0;


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

double interpolate (double a, double b, double c, double l, double m){
    return l + ((c-a)/(b-a))*(m-l);
}

void init(void)
{

    const char* Vshader_render = textFileRead("textureMap.vert");

    const char* Fshader_render = textFileRead("textureMap.frag");
    shader_texture.init(Vshader_render, Fshader_render, 0);




    const char* Vshader_cube = textFileRead("renderShape.vert");
    const char* Fshader_cube = textFileRead("passThrough.frag");

    shader_cube.init(Vshader_cube, Fshader_cube, 0);


    createSquare();

    //Column Major Order
    float near = 1;
    float far = 100;
    K_camera = glm::mat4(535.4f, 0.0f, 0.0f, 0.0f,
                         0.0f, 539.2f, 0.0f, 0.0f,
                         -320.1f, -247.6f, near+far, -1.0f,
                         0.0f, 0.0f, near*far, 0.0f);
    K_camera = glm::ortho(0.0f,640.0f,0.0f,480.0f,near,far)*K_camera;
    //invK = glm::inverse(K_camera);
}
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
    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        pos[0] += 0.01;
        std::cout<<pos[0]<<std::endl;
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        pos[0] -= 0.01;
        std::cout<<pos[0]<<std::endl;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        pos[1] -= 0.01;
        std::cout<<pos[1]<<std::endl;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        pos[1] += 0.01;
        std::cout<<pos[1]<<std::endl;
    }
    if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        pos[2] -= 0.01;
        std::cout<<pos[2]<<std::endl;
    }
    if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || (action == GLFW_REPEAT)))
    {
        pos[2] += 0.01;
        std::cout<<pos[2]<<std::endl;
    }
    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS ))
    {
        play = 1-play;
    }
}


void display(void)
{
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    if(!incomingImage) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &incomingImage);
        glBindTexture(GL_TEXTURE_2D, incomingImage);
        glTexImage2D(GL_TEXTURE_2D, 0,  GL_R16F , pngObject.width, pngObject.height, 0,   GL_RED,  GL_UNSIGNED_SHORT, &pngObject.depthMap[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);


    }
    else if(play){
        glBindTexture(GL_TEXTURE_2D, incomingImage);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,  pngObject.width, pngObject.height,  GL_RED,  GL_UNSIGNED_SHORT, &pngObject.depthMap[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
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
        glUniform3f(shader_cube.shaderUniform("alterPosition"),pos[0],pos[1],pos[2]);

        float w = interpolate(stod(qdata[locframe][0]),stod(qdata[locframe+1][0]),stod(imageFiles[frame][0]),
                stod(qdata[locframe][7]),stod(qdata[locframe+1][7]));
        float x = interpolate(stod(qdata[locframe][0]),stod(qdata[locframe+1][0]),stod(imageFiles[frame][0]),
                stod(qdata[locframe][4]),stod(qdata[locframe+1][4]));
        float y = interpolate(stod(qdata[locframe][0]),stod(qdata[locframe+1][0]),stod(imageFiles[frame][0]),
                stod(qdata[locframe][5]),stod(qdata[locframe+1][5]));
        float z = interpolate(stod(qdata[locframe][0]),stod(qdata[locframe+1][0]),stod(imageFiles[frame][0]),
                stod(qdata[locframe][6]),stod(qdata[locframe+1][6]));

        glm::quat q(w,x,y,z);
        glm::mat3 Model = glm::mat3_cast(glm::normalize(base));
        glm::mat3 Rmat = glm::mat3_cast(glm::normalize(q));
//        Rmat[2] = -Rmat[2];
//        Rmat = -Rmat;
        //std::cout<<glm::to_string(glm::determinant(Rmat));
        Rmat = glm::transpose(Rmat);
        std::cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<" "<<scale<<std::endl;

//        std::cout<<frame<<std::endl;
//        std::cout<<locframe<<std::endl;

        glUniform3f(shader_cube.shaderUniform("t_gk"),stod(qdata[locframe][1]), stod(qdata[locframe][2]),stod(qdata[locframe][3]));
        glUniformMatrix3fv(shader_cube.shaderUniform("invR"),1,GL_FALSE,&Rmat[0][0]);
        glUniformMatrix3fv(shader_cube.shaderUniform("ModelR"),1,GL_FALSE,&Model[0][0]);
        glUniformMatrix4fv(shader_cube.shaderUniform("K_camera"),1,GL_TRUE,&K_camera[0][0]);
//        glUniformMatrix4fv(shader_cube.shaderUniform("InverseK"),1,GL_FALSE,&invK[0][0]);


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
    if(argc < 2)
        throw "VERY FEW ARGUMENTS";
    std::string path(argv[1]);
    imageFiles.open((path+"depth.txt").c_str());
    qdata.open((path+"groundtruth.txt").c_str());

    frame = 1;
    locframe = 1;
    while (!glfwWindowShouldClose(window) && frame < imageFiles.getLength()){

        pngObject.readPngDepthMap((path+imageFiles[frame][1]).c_str());
        while(stod(qdata[locframe][0])<stod(imageFiles[frame][0]) && stod(qdata[locframe+1][0])<stod(imageFiles[frame][0]))
            locframe++;
        display();

        glfwSetFPSinTitle(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
        if(play)
            frame++;

    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

