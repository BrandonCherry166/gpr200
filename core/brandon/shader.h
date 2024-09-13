#ifndef SHADER_H
#define SHADER_H
#pragma once

#include "..\ew\external\glad.h" //Include glad for OpenGL Headers
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>

class Shader {
public:
	unsigned int ID;

	//Constructor to build Shader
	Shader(const char* vertexPath, const char* fragmentPath);
	
	//Activate Shader
	void use();

	//utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

};
#endif