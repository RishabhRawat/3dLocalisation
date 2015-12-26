#include <iostream>
#include "voxelOperations.h"
#include "marchingCubes.h"
#include "voxel.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext.hpp>  

#define CLIP_D 0.03f
#define VOXEL_INTERNAL_FORMAT GL_RGBA

Shader shader_rendering;
Shader shader_merging;

glm::mat4 MVP;
glm::mat4 Projection, View, Model;
glm::mat3 K_camera, invK;

GLuint texID[2];
GLuint lookupTableTexture;
GLuint incomingImage;
GLuint FramebufferName;

GLuint gVAO, gVBO;

Voxel pngObject;

// read from ping write to pong (pong = 1-ping)
int ping;

void createSquare(void)
{
	glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
	// make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	// Put the three triangle verticies into the VBO
    GLfloat vertexData[(VOXELNUM-1)*(VOXELNUM-1)*(VOXELNUM-1)*3+3];
    std::cout<<"size: "<<VOXELNUM<<std::endl;

    for (unsigned int z = 0; z < (VOXELNUM-1); z++) {
		for (unsigned int y = 0; y < (VOXELNUM-1); y++) {
			for (unsigned int x = 0; x < (VOXELNUM-1); x++) {
				vertexData[(x+(VOXELNUM-1)*y+z*(VOXELNUM-1)*(VOXELNUM-1))*3] = (float)x;
				vertexData[(x+(VOXELNUM-1)*y+z*(VOXELNUM-1)*(VOXELNUM-1))*3+1] = (float)y;
				vertexData[(x+(VOXELNUM-1)*y+z*(VOXELNUM-1)*(VOXELNUM-1))*3+2] = (float)z;
			}
		}
    }

    vertexData[(VOXELNUM-1)*(VOXELNUM-1)*(VOXELNUM-1)*3] = (VOXELNUM-1);
	vertexData[(VOXELNUM-1)*(VOXELNUM-1)*(VOXELNUM-1)*3+1] = -1;
	vertexData[(VOXELNUM-1)*(VOXELNUM-1)*(VOXELNUM-1)*3+2] = -1;

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    // connect the xyz to the "vPosition" attribute of the vertex shader
	GLint attrib = glGetAttribLocation(shader_rendering.shader_id, "Vertex");
    glEnableVertexAttribArray(attrib);
	
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_TRUE,3*sizeof(GLfloat), NULL);
	
    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}  

void init(void)
{
    // shader = new Shader();
	//assuming VOXELNUM = 4
	glGenTextures(1, &lookupTableTexture);
	glBindTexture(GL_TEXTURE_2D, lookupTableTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8I, 16, 256, 0,  GL_RED_INTEGER, GL_BYTE, &triTable[0][0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	
	texID[0] = utilCreate3DVoxel(VOXELNUM);
	texID[1] = utilCreate3DVoxel(VOXELNUM);


    const char* Vshader_render = "#version 440 \n in vec3 Vertex;\nvoid "
                          "main() {	\n	gl_Position = vec4(Vertex,1.0);\n}";
    const char* Gshader_render = textFileRead("simpleG.geo");
    //const char* Gshader = textFileRead("error2.geo");

	const char* Fshader_render = textFileRead("simpleFshader.frag");
    shader_rendering.init(Vshader_render, Fshader_render, Gshader_render, 0);



    glGenTextures(1, &incomingImage);
	glBindTexture(GL_TEXTURE_2D, incomingImage);
	glTexImage2D(GL_TEXTURE_2D, 0,  GL_R16F , pngObject.width, pngObject.height, 0,   GL_RED,  GL_UNSIGNED_SHORT, &pngObject.depthMap[0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);


    ping = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, texID[0],0);
    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1, texID[1],0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    const char* Gshader_merge = textFileRead("simpleLayeredRender.geo");
    const char* Fshader_merge = textFileRead("mergeVoxels.frag");

    shader_merging.init(Vshader_render, Fshader_merge, Gshader_merge, 0);


	createSquare();

	K_camera = glm::mat3(535.4, 0, 320.1, 0, 539.2, 247.6, 0, 0, 1);
	invK = glm::inverse(K_camera);
}

void display(void)
{
	int intl;
	glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // glViewport(0,0,VOXELNUM,VOXELNUM);

    {
		glViewport(0,0,VOXELNUM,VOXELNUM);	
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		shader_merging.bind();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_3D, texID[ping]);
		glUniform1i(shader_merging.shaderUniform("pingVoxel"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, incomingImage);
		glUniform1i(shader_merging.shaderUniform("depthMap"), 1);

		glUniform1ui(shader_merging.shaderUniform("mu"),CLIP_D);
		glUniform1i(shader_merging.shaderUniform("voxelDepth"),VOXELNUM);
		// -2.1510 0.6848 1.4888 -0.2495 0.7955 -0.5204 0.1843
		glm::quat q(0.1843, -0.2495, 0.7955, -0.5204);
		glm::mat3 Rmat = glm::mat3_cast(q);
		Rmat = glm::inverse(Rmat);
		glUniform3f(shader_merging.shaderUniform("t_gk"),-2.1510, 0.6848, 1.4888);
		glUniformMatrix3fv(shader_merging.shaderUniform("inv_R_gk"),1,GL_FALSE,&Rmat[0][0]);
		glUniformMatrix3fv(shader_merging.shaderUniform("K_camera"),1,GL_TRUE,&K_camera[0][0]);
		glUniformMatrix3fv(shader_merging.shaderUniform("InverseK"),1,GL_TRUE,&invK[0][0]);

		GLenum attachment  = GL_COLOR_ATTACHMENT0+(1-ping);
		glDrawBuffers(1, &attachment);
		
		glBindVertexArray(gVAO);
	    glDrawArrays(GL_POINTS, (VOXELNUM-1)*((VOXELNUM-1)*(VOXELNUM-1)-1), VOXELNUM);
	    glBindVertexArray(0); // Unbind our Vertex Array Object
		

		
		shader_merging.unbind();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

	{
		glViewport(0,0,500,500);
	    shader_rendering.bind();
		glUniform4fv(shader_rendering.shaderUniform("cubeVector"), 8*4,&cubeVector[0][0]);
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_3D, texID[0]);

	    glUniform1i(shader_rendering.shaderUniform("my_color_texture"), 0);
	    glUniform1i(shader_rendering.shaderUniform("my_data_texture"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, lookupTableTexture);
		glUniform1i(shader_rendering.shaderUniform("lookupTableTexture"), 1);
		
	    glUniformMatrix4fv(shader_rendering.shaderUniform("Transform"), 1, GL_FALSE, glm::value_ptr(MVP));
	    glBindVertexArray(gVAO);
	    glDrawArrays(GL_POINTS, 0, (VOXELNUM-1)*(VOXELNUM-1)*(VOXELNUM-1));
	    glBindVertexArray(0); // Unbind our Vertex Array Object
	    
	    shader_rendering.unbind();
	}
}

void reshape(int width, int height)
{
    /*
    if(width > height){
            identityMat[0]= 1.0;//height/width;
            identityMat[5]= 1.0f;
    }
    else{
            identityMat[5]= 1.0;//height/width;
            identityMat[0]= 1.0f;
    }*/
}
bool sticky, drag;
double oldx, oldy;
double dx, dy;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		sticky = true;
		drag = true;
		dx = 0;
		dy = 0;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		sticky = false;
		if(dx != 0 && dy != 0)
		{
			float leng = std::sqrt(dx*dx+dy*dy)/300.0f;
			Model = glm::rotate(Model, leng, glm::normalize(glm::vec3(dy, dx, 0.0f)));
			MVP = Projection * View * Model;
			dx = 0;
			dy = 0;
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(yoffset > 0)
		Model = glm::scale(Model, glm::vec3(0.9f));
	else
		Model = glm::scale(Model, glm::vec3(1/0.9f));
	MVP = Projection * View * Model;
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(drag)
	{
		oldx = xpos;
		oldy = ypos;
		drag = false;
	}
	if(sticky)
	{
		dx = xpos-oldx;
		dy = ypos-oldy;
		if(dx*dy == 0)
			return;
		float leng = std::sqrt(dx*dx+dy*dy)/300.0f;
		
		MVP = Projection * View * glm::rotate(Model, leng, glm::normalize(glm::vec3(dy, dx, 0.0f)));
	}
}





static void openglCallbackFunction(GLenum source,
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

void glfw_error_callback(int error, const char* description)
{
	std::cout<<"ERROR: ";
    fputs(description, stderr);
    std::cout<<std::endl;
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
	
	GLFWwindow* window = glfwCreateWindow(500, 500, "My Title", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	
	
	glfwSwapInterval(1);
	pngObject.readPngDepthMap("1341841873.505863.png");
	 
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
	
	
	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, NULL);
	GLuint unusedIds = 0;
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
	
	init();
	
	int nbFrames;
	double currentTime = 0;
	double lastTime = 0;
	while (!glfwWindowShouldClose(window)){
	    display();

	    // Measure speed
	    double currentTime = glfwGetTime();
	    nbFrames++;

	    if (currentTime - lastTime >= 1.0) { // If last cout was more than 1 sec ago
	        char title[256];
	        title[255] = '\0';

	        snprintf(title, 255, "FPS: %d", nbFrames);

	        glfwSetWindowTitle(window, title);

	        nbFrames = 0;
	        lastTime += 1.0;
	    }

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

