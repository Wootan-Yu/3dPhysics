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
	Shader skyboxShader;

	Shader guitarBackpackShader;
	Model guitarBackpackModel;

	Shader sponzaShader;
	Model sponzaModel;

	Shader spaceHelmetShader;
	Model spaceHelmetModel;

	Shader planetShader;
	Model planetModel;

	Shader asteroidShader;
	Model asteroidModel;

	glm::mat4* modelMatrices;
	std::vector<glm::vec3> asteroidOffsets;
	std::vector<float> asteroidScales;
	std::vector<float> asteroidBaseAngles;
	unsigned int buffer;

	Camera camera;
	float currentFrame = 0.0f;
	GLuint VBOcube, VAOcube;
	GLuint VBOplane, VAOplane;
	GLuint VBOlightCube, VAOlightCube;
	GLuint VAOobject;
	GLuint VBOskybox, VAOskybox;

	GLuint texture1; //cube
	GLuint texture2; //plane
	GLuint texture3; //object cube
	GLuint texture4; //object cube
	GLuint textureCubeMap;

	glm::vec3 pointLightPositions[4];

	Engine();
	~Engine();
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


inline unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		std::cout << faces[i] << '\n';
		stbi_set_flip_vertically_on_load(false);
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		stbi_set_flip_vertically_on_load(true);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}