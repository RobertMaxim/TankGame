#include "Mesh.h"

#include<filesystem>

namespace fs = std::filesystem;

#define width 800
#define height 800

Vertex vertices[] = {
	   glm::vec3(-0.5f,0.0f,0.5f), glm::vec3(1.0f,0.0f,0.0f), glm::vec2(0.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f),
	   glm::vec3(-0.5f,0.0f,-0.5f),glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f),
	   glm::vec3(0.5f,0.0f,-0.5f), glm::vec3(0.0f,0.0f,1.0f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f),
	   glm::vec3(0.5f,0.0f,0.5f), glm::vec3(0.0f,0.0f,1.0f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f)
};


GLuint indices[] = {
	0,1,2,
	0,2,3
};



void Initialize() {
	
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(width, height, "Lab 6", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	


	glfwMakeContextCurrent(window);

	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // culoarea de fond a ecranului
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texturePath = "/Resources/";

	Texture textures[] = {
		Texture((parentDir + texturePath + "grass.jpg").c_str(),"diffuse",0 ,GL_RGBA,GL_UNSIGNED_BYTE)
	};

	Shader shaderProgram("Field.vs", "Field.fs");

	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(verts, ind, tex);

	glEnable(GL_DEPTH_TEST);
	// Create camera
	Camera pCamera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		pCamera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		pCamera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Draws different meshes
		floor.Draw(shaderProgram, pCamera);
		//light.Draw(lightShader, pCamera);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	//Cleanup();
	
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	
	return 0;
}
