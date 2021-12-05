#pragma once
#include "Texture.h"
#include "Camera.h"
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texUV;
	glm::vec3 normal;
};



class Mesh {
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	GLuint vaoID, VBO, EBO;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);

};