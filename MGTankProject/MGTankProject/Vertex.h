#pragma once
#include "Headers.h"
#include <iostream>
#include "Camera.h"
#include "Shader.h"

Camera* pCamera;
GLuint VAO, VBO, EBO;



void CreateVBO()
{
	GLfloat vertices[] = {
	   -0.5f,  0.f, 0.5f,   1.f, 0.f, 0.f,   0.1f, 1.f,
	   -0.5f, 0.f, -0.5f,   0.f, 1.f, 0.f,   0.f, 0.f,
	   0.5f, 0.f, 0.5f,  0.f, 0.f, 1.f,   1.f, 0.f,
	   0.5f,  0.f, 0.5f,  1.f, 1.f, 0.f,   1.f, 1.f
	};
	unsigned int indices[] = {
	   0, 1, 2,
	   0, 2, 3
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
void DestroyVBO()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Cleanup()
{
	DestroyShaders();
	DestroyVBO();

	delete pCamera;
}

void CreateTextures(const std::string& strExePath)
{
	// load and create a texture 
	// -------------------------
	// texture 1
	// ---------
	glGenTextures(1, &texture1Location);
	glBindTexture(GL_TEXTURE_2D, texture1Location);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load((strExePath + "\\stones.jpg").c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &texture2Location);
	glBindTexture(GL_TEXTURE_2D, texture2Location);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load((strExePath + "\\Bricks.jpg").c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}


void RenderCube()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	int indexArraySize;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &indexArraySize);
	glDrawElements(GL_TRIANGLES, indexArraySize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

void RenderFunction()
{
	glm::vec3 cubePositions[] = {
	   glm::vec3(-1.0f,  0.0f, -5.0f),
	   glm::vec3(0.0f,  0.0f,   -5.0f),
	   glm::vec3(-1.0f,  0.0f,  -4.0f),
	   glm::vec3(0.0f, 0.0f,  -4.0f),
	   glm::vec3(-1.0f, 0.0f,  -3.0f),
	   glm::vec3(0.0f,  0.0f,  -3.0f),
	   glm::vec3(-1.0f,  0.0f, -2.0f),
	   glm::vec3(0.0f, 0.0f, -2.0f),
	   glm::vec3(-1.0f, 0.0f, -1.0f),
	   glm::vec3(0.0f,  0.0f, -1.0f),
	   glm::vec3(-1.0f,  0.0f,   0.0f),
	   glm::vec3(0.0f,  0.0f,   0.0f),
	   glm::vec3(-1.0f,  0.0f,   5.0f),
	   glm::vec3(0.0f,  0.0f,   5.0f),
	   glm::vec3(-1.0f,  0.0f,   4.0f),
	   glm::vec3(0.0f,  0.0f,   4.0f),
	   glm::vec3(-1.0f,  0.0f,   3.0f),
	   glm::vec3(0.0f,  0.0f,   3.0f),
	   glm::vec3(-1.0f,  0.0f,   2.0f),
	   glm::vec3(0.0f,  0.0f,   2.0f),
	   glm::vec3(-1.0f,  0.0f,   1.0f),
	   glm::vec3(0.0f,  0.0f,   1.0f),
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(ProgramId);

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1Location);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2Location);

	glm::mat4 projection = pCamera->GetProjectionMatrix();
	glUniformMatrix4fv(ProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 view = pCamera->GetViewMatrix();
	glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));

	/*glm::mat4 view;
	float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));*/

	glBindVertexArray(VAO);
	glUniform1i(glGetUniformLocation(ProgramId, "textureOption"), 0);
	for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 worldTransf = glm::translate(glm::mat4(1.0), cubePositions[i]);
		glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransf));

		RenderCube();
	}
}

void Initialize(const std::string& strExePath)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // culoarea de fond a ecranului
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	CreateVBO();
	CreateShaders();
	CreateTextures(strExePath);

	// Create camera
	pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.5, 0.5, 10));
}