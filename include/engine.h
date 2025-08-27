#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include <random>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <openglDebug.h>
#include <demoShaderLoader.h>

#include "global.h"
#include "userInput.h"
#include "camera.h"

#include "model.h"
#include "mesh.h"

struct Engine {
	GLFWwindow* window;
	Shader shader;
	Shader lightCubeShader;
	Shader objectShader;
	Shader modelShader;
	Model modelObject;

	Camera camera;
	float currentFrame = 0.0f;
	GLuint VBOcube, VAOcube;
	GLuint VBOplane, VAOplane;
	GLuint VBOlightCube, VAOlightCube;
	GLuint VAOobject;

	GLuint texture1; //cube
	GLuint texture2; //plane
	GLuint texture3; //object cube
	GLuint texture4; //object cube

	glm::vec3 pointLightPositions[4];

	Engine();
	void init();
	void initShape();
	void initShader();
	void initTexture();
	void run();
	void update();
	void processInput();
	void keyInput();
	void drawShape();
	void render();
};