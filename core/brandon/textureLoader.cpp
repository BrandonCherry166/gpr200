#define STB_IMAGE_IMPLEMENTATION
#include "..\ew\external\stb_image.h" //Include stbi
#include <string>
#include <iostream>
#include "textureLoader.h"
#include "..\ew\external\glad.h"

unsigned int loadTexture2D(const char* filePath, int filterMode, int wrapMode, bool flipIt)
{
	unsigned int texture1;
	int width, height, nrChannels;

	if (flipIt)
	{
		stbi_set_flip_vertically_on_load(true);
	}
	else
	{
		stbi_set_flip_vertically_on_load(false);
	}
	
	//texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	//Texture Wrapping Properties
	glTexParameteri(GL_TEXTURE_2D, wrapMode, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	//Filtering Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return texture1;
}