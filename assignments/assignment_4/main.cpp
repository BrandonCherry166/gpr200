#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "..\core\brandon\textureLoader.h"
#include "..\core\brandon\shader.h"
#include "..\core\brandon\camera.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
void processInput(GLFWwindow* window);


//Camera
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f; //Time between first and last frame
float lastFrame = 0.0f;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
unsigned int indices[] = {
	0,1,3, //Triangle 1
	1,2,3 //Triangle 2
};

// glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f))

glm::vec3 cubePositions[] = {
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
	glm::vec3(ew::RandomRange(-4.0f, 4.0f), ew::RandomRange(-3.0f, 5.0f), ew::RandomRange(-15.0f, 0.0f)),
};

float randomRotation = ew::RandomRange(-90.0f, 90.0f);

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
	glEnable(GL_DEPTH_TEST);
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

	Shader ourShader("assets/vertexShader.vs", "assets/fragmentShader.fs");

	//Linking Vertex Attributes - Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Texture Attributes
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	unsigned int texture = loadTexture2D("assets/texture.png", GL_LINEAR, GL_MIRRORED_REPEAT, false);
	unsigned int texture2 = loadTexture2D("assets/newSprite.png", GL_NEAREST, GL_CLAMP_TO_EDGE, true);

	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);
	//Render loop
	while (!glfwWindowShouldClose(window)) {
	
		glfwPollEvents();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		
		//Clear Colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = randomRotation * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//Draw
		glfwSwapBuffers(window);
		
		
	}
	printf("Shutting down...");
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.ProcessKeyboard(FORWARD, deltaTime);
		std::cout << "Input!";
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cam.ProcessKeyboard(STRAFE_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cam.ProcessKeyboard(STRAFE_RIGHT, deltaTime);
}
