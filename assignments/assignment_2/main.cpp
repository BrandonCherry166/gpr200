#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "..\core\brandon\textureLoader.h"
#include "..\core\brandon\shader.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
		//Positions			//Colors
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {
	0,1,3, //Triangle 1
	1,2,3 //Triangle 2
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

	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("assets/vertexShader.vs", "assets/fragmentShader.fs");
	Shader spriteShader("assets/spriteVertexShader.vs", "assets/spriteFragmentShader.fs");

	
	//Linking Vertex Attributes - Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	
	//Texture Attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	unsigned int texture = loadTexture2D("assets/texture.png", GL_LINEAR, GL_MIRRORED_REPEAT, false);
	unsigned int texture2 = loadTexture2D("assets/newSprite.png", GL_NEAREST, GL_CLAMP_TO_EDGE, true);

	ourShader.setInt("texture1", 1);
	spriteShader.setInt("texture1", 1);
	//Render loop
	while (!glfwWindowShouldClose(window)) {
	
		glfwPollEvents();
		float time = (float)glfwGetTime();
		//Clear Colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	
		
		ourShader.use();
		

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		spriteShader.use();

		//Time Stuff
		float timeValue = glfwGetTime();
		int timeLoc = glGetUniformLocation(spriteShader.ID, "uTime");
		glUniform1f(timeLoc, time);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//Draw
		glfwSwapBuffers(window);
		
		
	}
	printf("Shutting down...");
}
