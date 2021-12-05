#pragma once
#include "Shader.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int width; //dimensiuni fereastra
	int height;

	float speed = 0.1f; //viteza camera
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position);

	const glm::mat4 GetViewMatrix() const;
	//const glm::mat4 GetProjMatrix() const;
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane); // adapteaza la vertex shader matricea camerei
	void Matrix(Shader& shader, const char* uniform); // exporta in shader matricea camerei
	void Inputs(GLFWwindow* window); 
};