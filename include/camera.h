#pragma once

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

struct Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection; //front
	const glm::vec3 up;
	
	glm::vec3 strafeDirection;

	Camera();
	glm::mat4 getWorldToViewMatrix() const;

	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void moveUp(float deltaTime);
	void moveDown(float deltaTime);

};