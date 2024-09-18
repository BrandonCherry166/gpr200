#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "..\ew\external\stb_image.h" //Include stbi
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>



unsigned int loadTexture2D(const char* filePath, int filterMode, int wrapMode);
#endif