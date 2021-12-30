//#include "Texture.h"
//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
///*unsigned int CreateTexture(const std::string& strTexturePath)
//{
//    
//}*/
//Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType){}
////{
////	// Assigns the type of the texture ot the texture object
////	type = texType;
////
////	// Stores the width, height, and the number of color channels of the image
////	int widthImg, heightImg, numColCh;
////	// Flips the image so it appears right side up
////	stbi_set_flip_vertically_on_load(true);
////	// Reads the image from a file and stores it in bytes
////	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
////
////	// Generates an OpenGL texture object
////	glGenTextures(1, &ID);
////	// Assigns the texture to a Texture Unit
////	glActiveTexture(GL_TEXTURE0 + slot);
////	unit = slot;
////	glBindTexture(GL_TEXTURE_2D, ID);
////
////	// Configures the type of algorithm that is used to make the image smaller or bigger
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////
////	// Configures the way the texture repeats (if it does at all)
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
////
////	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
////	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
////	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
////
////	// Assigns the image to the OpenGL Texture object
////	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
////	// Generates MipMaps
////	glGenerateMipmap(GL_TEXTURE_2D);
////
////	// Deletes the image data as it is already in the OpenGL Texture object
////	stbi_image_free(bytes);
////
////	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
////	glBindTexture(GL_TEXTURE_2D, 0);
////}
//
//void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
//{
//	// Gets the location of the uniform
//	GLuint texUni = glGetUniformLocation(shader.GetID(), uniform);
//	// Shader needs to be activated before changing the value of a uniform
//	glUseProgram(shader.GetID());
//	// Sets the value of the uniform
//	glUniform1i(texUni, unit);
//}
//
//void Texture::Bind()
//{
//	glActiveTexture(GL_TEXTURE0 + unit);
//	glBindTexture(GL_TEXTURE_2D, ID);
//}
//
//void Texture::Unbind()
//{
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//unsigned int Texture::CreateTexture(const std::string& strTexturePath)
//{
//	unsigned int textureId = -1;
//
//	// load image, create texture and generate mipmaps
//	int width, height, nrChannels;
//	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	unsigned char* data = stbi_load(strTexturePath.c_str(), &width, &height, &nrChannels, 0);
//	if (data) {
//		GLenum format{};
//		if (nrChannels == 1)
//			format = GL_RED;
//		else if (nrChannels == 3)
//			format = GL_RGB;
//		else if (nrChannels == 4)
//			format = GL_RGBA;
//
//		glGenTextures(1, &textureId);
//		glBindTexture(GL_TEXTURE_2D, textureId);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		// set the texture wrapping parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//		// set texture filtering parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//	else {
//		std::cout << "Failed to load texture: " << strTexturePath << std::endl;
//	}
//	stbi_image_free(data);
//
//	return textureId;
//}
//
//Texture Texture::loadCubemap(const std::vector<std::string>& texpaths){
//
//	// If not enough images, return empty texture.
//
//	if (texpaths.size() != 6) {
//		return (*this);
//	}
//
//	// Create and bind texture.
//
//	GLuint textureId;
//	glGenTextures(1, &textureId);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
//
//	// Texture settings.
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	std::vector<unsigned char> image;
//	int components = 4;
//	int width = 0;
//	int height = 0;
//
//	// For each side, load the image and upload it in the right slot.
//	// We don't need to flip them.
//
//	stbi_set_flip_vertically_on_load(false);
//
//	for (size_t side = 0; side < 6; ++side) {
//		unsigned char* image = stbi_load(texpaths[side].c_str(), &width, &height, NULL, components);
//		if (image == NULL) {
//			std::cerr << "Unable to load the texture at path " << texpaths[side] << "." << std::endl;
//			return (*this);
//		}
//		glTexImage2D(GLenum(GL_TEXTURE_CUBE_MAP_POSITIVE_X + side), 0, GL_SRGB8_ALPHA8 /*: GL_RGBA*/, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(image[0]));
//		free(image);
//	}
//	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
//
//	this->ID = textureId;
//	return (*this);
//}
//
//
//void Texture::Delete()
//{
//	glDeleteTextures(1, &ID);
//}
//#endif