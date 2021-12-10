#include "Mesh.h"

#include<filesystem>

namespace fs = std::filesystem;

#define width 800
#define height 800
Camera* pCamera = nullptr;

Vertex vertices[] = {
	   glm::vec3(-5.5f,0.0f,0.5f), glm::vec3(0.0f,0.0f,0.0f), glm::vec2(0.0f,10.0f), glm::vec3(0.0f,1.0f,0.0f),
	   glm::vec3(-5.5f,0.0f,-0.5f),glm::vec3(0.0f,0.0f,0.0f), glm::vec2(0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f),
	   glm::vec3(5.5f,0.0f,-0.5f), glm::vec3(0.0f,0.0f,0.0f), glm::vec2(10.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f),
	   glm::vec3(5.5f,0.0f,0.5f), glm::vec3(0.0f,0.0f,0.0f), glm::vec2(10.0f,10.0f), glm::vec3(0.0f,1.0f,0.0f)
};


GLuint indices[] = {
	0,1,2,
	0,2,3
};


void RenderFunction(Shader& shaderProgram, Texture textures[], Camera* pCamera, Mesh& floor)
{
	glm::vec3 cubePositions[] = {
	   glm::vec3(-1.0f, 0.0f,-5.0f),
	   glm::vec3(0.0f,0.0f,-5.0f),
	   glm::vec3(-1.0f,0.0f,-4.0f),
	   glm::vec3(0.0f,0.0f,-4.0f),
	   glm::vec3(-1.0f, 0.0f,-3.0f),
	   glm::vec3(0.0f,0.0f,-3.0f),
	   glm::vec3(-1.0f,0.0f,-2.0f),
	   glm::vec3(0.0f,0.0f,-2.0f),
	   glm::vec3(-1.0f,0.0f,-1.0f),
	   glm::vec3(0.0f,0.0f,-1.0f),
	   glm::vec3(-1.0f,0.0f,0.0f),
	   glm::vec3(0.0f,0.0f,0.0f),
	   glm::vec3(-1.0f,0.0f,5.0f),
	   glm::vec3(0.0f,0.0f,5.0f),
	   glm::vec3(-1.0f,0.0f,4.0f),
	   glm::vec3(0.0f,0.0f,4.0f),
	   glm::vec3(-1.0f,0.0f,3.0f),
	   glm::vec3(0.0f,0.0f,3.0f),
	   glm::vec3(-1.0f,0.0f,2.0f),
	   glm::vec3(0.0f,0.0f,2.0f),
	   glm::vec3(-1.0f,0.0f,1.0f),
	   glm::vec3(0.0f,0.0f,1.0f),
	};

	/*glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f,  0.0f,   0.0f),
	   glm::vec3(-5.0f,  5.0f,  5.0f),
	   glm::vec3(-5.0f, -5.0f,  5.0f),
	   glm::vec3(5.0f, -5.0f,  5.0f),
	   glm::vec3(5.0f,  5.0f,  5.0f),
	   glm::vec3(-5.0f,  5.0f, -5.0f),
	   glm::vec3(-5.0f, -5.0f, -5.0f),
	   glm::vec3(5.0f, -5.0f, -5.0f),
	   glm::vec3(5.0f,  5.0f, -5.0f),
	};*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram.GetID());

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0].ID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1].ID);

	glm::mat4 projection = pCamera->GetProjectionMatrix();
	glUniformMatrix4fv(shaderProgram.ProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 view = pCamera->GetViewMatrix();
	glUniformMatrix4fv(shaderProgram.ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));



	glBindVertexArray(floor.getVAO());

	for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 worldTransf = glm::translate(glm::mat4(1.0), cubePositions[i]);
		glUniformMatrix4fv(shaderProgram.WorldMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransf));

		glBindBuffer(GL_ARRAY_BUFFER, floor.getVBO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floor.getEBO());

		int indexArraySize;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &indexArraySize);
		glDrawElements(GL_TRIANGLES, indexArraySize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}

double deltaTime = 0.0f;
double lastFrame = 0.0f;


void processInput(GLFWwindow* window, Camera* pCamera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pCamera->ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pCamera->ProcessKeyboard(UP, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pCamera->ProcessKeyboard(DOWN, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		int scrwidth, scrheight;
		glfwGetWindowSize(window, &scrwidth, &scrheight);
		pCamera->Reset(scrwidth, scrheight);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int scrwidth, int scrheight)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	pCamera->Reshape(scrwidth, scrheight);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	pCamera->MouseControl((float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
	pCamera->ProcessMouseScroll((float)yOffset);
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "Tank Simulator", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	pCamera = new Camera (width, height, glm::vec3(0.0f, 3.0f, 5.0f));

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texturePath = "/Resources/";
	unsigned int floorTexture = CreateTexture(parentDir+texturePath + "\\ColoredFloor.jpg");
	Texture textures[] = {
		Texture((parentDir + texturePath + "ice.jpg").c_str(),"diffuse", 0 ,GL_RGB,GL_UNSIGNED_BYTE),
		Texture((parentDir + texturePath + "ice.jpg").c_str(),"specular", 0 , GL_RGB, GL_UNSIGNED_BYTE)
	};

	Shader shadowMappingShader("Field.vs", "Field.fs");

	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(verts, ind, tex);

	glEnable(GL_DEPTH_TEST);
	// Create camera

	shadowMappingShader.Use();
	shadowMappingShader.SetInt("diffuseTexture", 0);
	shadowMappingShader.SetInt("shadowMap", 1);


	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window, pCamera);

		// Handles camera inputs
		// Updates and exports the camera matrix to the Vertex Shader


		// Draws different meshes
		floor.Draw(shadowMappingShader, pCamera);
		//light.Draw(lightShader, pCamera);

		RenderFunction(shadowMappingShader, textures, pCamera, floor);
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
safasfsafas