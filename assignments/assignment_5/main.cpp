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

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);


//Camera
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f; //Time between first and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, -8.0f);
glm::vec3 lightColor (1.0f, 1.0f, 1.0f);

float ambientK = 0.1f;
float diffuseK = 0.5f;
float spectralK = 0.5f;
float shine = 500;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
};



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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	

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

	Shader ourShader("assets/vertexShader.vs", "assets/fragmentShader.fs");
	Shader lightCubeShader("assets/lighting.vs", "assets/lighting.fs");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); // Normals
	glEnableVertexAttribArray(2);

	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	unsigned int texture = loadTexture2D("assets/texture.png", GL_LINEAR, GL_MIRRORED_REPEAT, false);
	
	ourShader.use();
	ourShader.setInt("texture1", 0);
	//Render loop
	while (!glfwWindowShouldClose(window)) {
	
		glfwPollEvents();
		//Draw ImGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//Create Settings
		ImGui::Begin("Settings");
		ImGui::SetWindowSize(ImVec2(400, 300));
		ImGui::SetWindowFocus("Settings");
		ImGui::Text("Add Settings Here");
		ImGui::DragFloat3("Light Position", &lightPos.x, 1.0f);
		ImGui::ColorEdit3("LightColor", &lightColor.x);

		ImGui::SliderFloat("AmbientK", &ambientK, 0.0f, 1.0f);
		ImGui::SliderFloat("DiffuseK", &diffuseK, 0.0f, 1.0f);
		ImGui::SliderFloat("SpectralK", &spectralK, 0.0f, 1.0f);
		ImGui::SliderFloat("Shininess", &shine, 2.0f, 1024.0f);

		ImGui::End();

		
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		if (ImGui::IsWindowFocused())
		{
			std::cout << "Yes";
		}
	
		//Clear Colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		

		ourShader.use();

		ourShader.setVec3("lightColor", lightColor);
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", cam.cameraPos);

		ourShader.setFloat("AmbientK", ambientK);
		ourShader.setFloat("DiffuseK", diffuseK);
		ourShader.setFloat("SpectralK", spectralK);
		ourShader.setFloat("Shininess", shine);

		glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = cam.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);

		for (unsigned int i = 0; i < 20; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = randomRotation * (i + 1); 
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightCubeShader.setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		

		//Draw
		glfwSwapBuffers(window);
		
		
	}
	printf("Shutting down...");
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	bool sprint = false;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		sprint = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.ProcessKeyboard(FORWARD, deltaTime, sprint);
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(BACKWARD, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(LEFT, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(RIGHT, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cam.ProcessKeyboard(STRAFE_UP, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cam.ProcessKeyboard(STRAFE_DOWN, deltaTime, sprint);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	float xPosf = static_cast<float>(xPos);
	float yPosf = static_cast<float>(yPos);

	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
		if (firstMouse)
		{
			lastX = xPosf;
			lastY = yPosf;
			firstMouse = false;
		}

		float xOffset = xPosf - lastX;
		float yOffset = lastY - yPosf;

		lastX = xPosf;
		lastY = yPosf;

		cam.ProcessMouseInput(xOffset, yOffset);
	}
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	cam.processScroll(static_cast<float>(yOffset));
}