#ifndef CAMERA_H
#define CAMERA_H

#include "..\ew\external\glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	STRAFE_LEFT,
	STRAFE_RIGHT
};

//Defaults
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


struct Camera
{
	glm::vec3 cameraPos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSens;
	float zoom;

	//Constructor with vec3
	Camera(glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), float Yaw = YAW, float Pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSens(SENSITIVITY), zoom(ZOOM)
	{
		cameraPos = Pos;
		worldUp = Up;
		yaw = Yaw;
		pitch = Pitch;
		updateCameraVectors();
	}
	//Second Constructor with floats
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float Yaw, float Pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSens(SENSITIVITY), zoom(ZOOM)
	{
		cameraPos = glm::vec3(posX, posY, posZ);
		worldUp = glm::vec3(upX, upY, upZ);
		yaw = Yaw;
		pitch = Pitch;
		updateCameraVectors();
	 }

	glm::mat4 GetViewMatrix() //Return the view matrix
	{
		return glm::lookAt(cameraPos, cameraPos + front, up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime) //Handles WSAD+QE
	{
		float velocity = movementSpeed * deltaTime;
		switch (direction)
		{
		case FORWARD:
			cameraPos += front * velocity;
			break;
		case BACKWARD:
			cameraPos -= front * velocity;
			break;
		case RIGHT:
			cameraPos += right * velocity;
			break;
		case LEFT:
			cameraPos -= right * velocity;
			break;
		case STRAFE_LEFT:
			cameraPos += front * velocity;
			cameraPos -= right * velocity;
			break;
		case STRAFE_RIGHT:
			cameraPos += front * velocity;
			cameraPos += right * velocity;
			break;
		}
	}

	void ProcessMouseInput(float xOffset, float yOffset, GLboolean constrainPitch = true) //Processing the mouse movement, not zoom, that is separate
	{
		xOffset *= mouseSens;
		yOffset *= mouseSens;

		yaw += xOffset;
		pitch += yOffset;

		if (constrainPitch) //Keep pitch from going out of the bounds of -89 to 89
		{
			if (pitch > 89.0f)
			{
				pitch = 89.0f;
			}
				
			if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}

			updateCameraVectors();
		}
	}
	void processScroll(float yOffset)
	{
		zoom -= float(yOffset);
		if (zoom < 1.0f)
		{
			zoom = 1.0f;
		}
		if (zoom > 45.0f)
		{
			zoom = 45.0f;
		}
	}
private:
	void updateCameraVectors()
	{
		//Calculate newFront
		glm::vec3 newFront;
		newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newFront.y = sin(glm::radians(pitch));
		newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(newFront);

		//Calculate new right and up
		right = glm::normalize(glm::cross(front, worldUp)); //Normalized Cross-product of front and worldUp is right
		up = glm::normalize(glm::cross(right, front)); //Normalized Cross-Product of right and front is up


	}
};

#endif