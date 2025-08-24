#include "camera.h"

Camera::Camera()
	: position(0.0f, 0.0f, 3.0f),
	viewDirection(0.0f, 0.0f, -1.0f),
	up(0.0f, 1.0f, 0.0f),
	strafeDirection(0.f, 0.f, 0.f)
{

}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, up);
}

void Camera::moveForward(float deltaTime)
{
	position += deltaTime * viewDirection;
}

void Camera::moveBackward(float deltaTime)
{
	position -= deltaTime * viewDirection;
}

void Camera::moveLeft(float deltaTime)
{
	position -= glm::normalize(glm::cross(viewDirection, up)) * deltaTime; // move left
}

void Camera::moveRight(float deltaTime)
{
	position += glm::normalize(glm::cross(viewDirection, up)) * deltaTime; // move left
}

void Camera::moveUp(float deltaTime)
{
	position.y += deltaTime; // move up
}

void Camera::moveDown(float deltaTime)
{
	position.y -= deltaTime; // move down
}