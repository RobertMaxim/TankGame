#pragma once
#include "Headers.h"
#include <iostream>
#include "Camera.h"
#include "Shader.h"

Camera* pCamera;
GLuint VAO, VBO, EBO;


struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texUV;
	glm::vec3 normal;
};