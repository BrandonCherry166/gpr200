#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "..\core\brandon\shader.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
		//Positions			//Colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};


int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!

	//Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader ourShader("assets/vertexShader.vs", "assets/fragmentShader.fs");
	//More Shader Programming
	ourShader.use();
	

	//Linking Vertex Attributes - Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	//Render loop
	while (!glfwWindowShouldClose(window)) {
	
		glfwPollEvents();
		float time = (float)glfwGetTime();
		//Clear Colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.use();
		

		//Using Uniform for Color
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
		
		ourShader.use();

		int timeLoc = glGetUniformLocation(ourShader.ID, "uTime");
		glUniform1f(timeLoc, time);

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//Render Triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Draw
		glfwSwapBuffers(window);
		
		
	}
	printf("Shutting down...");
}
