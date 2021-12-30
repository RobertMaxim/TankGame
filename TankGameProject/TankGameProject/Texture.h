#pragma once
#include "Shader.h"
#include <vector>
class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;
	Texture() = default;
	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	unsigned int CreateTexture(const std::string& strTexturePath);

	Texture loadCubemap(const std::vector<std::string>& texpaths);

	void Delete();
};