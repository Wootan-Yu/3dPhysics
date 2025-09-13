#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include <stb_truetype/stb_truetype.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>

#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>


#include <openglDebug.h>
#include <demoShaderLoader.h>

#include "global.h"
#include "userInput.h"
#include "camera.h"

#include "model.h"
#include "mesh.h"




namespace Layers {
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 1;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
}

namespace BroadPhaseLayers {
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr unsigned NUM_LAYERS = 2;
}

class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface {
public:
	BPLayerInterfaceImpl() {
		mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
		mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
	}
	JPH::uint GetNumBroadPhaseLayers() const override { return BroadPhaseLayers::NUM_LAYERS; }
	JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override {
		JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
		return mObjectToBroadPhase[inLayer];
}
#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override {
		switch ((BroadPhaseLayer::Type)inLayer) {
		case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING: return "NON_MOVING";
		case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:     return "MOVING";
		default: return "UNKNOWN";
		}
	}
#endif
private:
	JPH::BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter {
public:
	bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override {
		// simple safe policy: moving collides with everything, non-moving only collides with moving
		if (inLayer1 == Layers::NON_MOVING) return inLayer2 == BroadPhaseLayers::MOVING;
		return true;
	}
};

class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter {
public:
	bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::ObjectLayer inLayer2) const override {
		// don't collide two non-moving objects
		if (inLayer1 == Layers::NON_MOVING && inLayer2 == Layers::NON_MOVING) return false;
		return true;
	}
};


// Store sphere vertex data
struct SphereMesh {
	std::vector<float> vertices;  // pos(3), normal(3), color(3)
	std::vector<unsigned int> indices;
};



struct Engine {
	GLFWwindow* window;
	Shader planeShader;
	
	Shader skyboxShader;

	Shader sponzaShader;
	Model sponzaModel;

	//shadow mapping
	Shader depthShader;
	GLuint depthMapFBO, depthMap;

	JPH::PhysicsSystem physicsSystem;
	JPH::BodyInterface* bodyInterface = nullptr;

	//sphere physics
	std::vector<JPH::BodyID> sphere_bodies;
	std::vector<glm::mat4> sphereModels;
	GLuint sphereInstanceVBO, VAOsphere, VBOsphere, EBOsphere;
	SphereMesh sphereObject;
	Shader sphereShader;

	float sphereMat[16];


	//cube physics
	JPH::BodyID cubeBodyID;
	float cubeMat[16];
	glm::mat4 cubeModel;

	GLuint VAOPhysicsCube, VBOPhysicsCube;
	GLuint VAOOutline, VBOOutline;
	
	Shader physicsCubeShader;
	Shader outlineShader;



	glm::mat4* modelMatrices;
	std::vector<glm::vec3> asteroidOffsets;
	std::vector<float> asteroidScales;
	std::vector<float> asteroidBaseAngles;
	unsigned int buffer;

	Camera camera;
	float currentFrame = 0.0f;
	GLuint VBOplane, VAOplane, planeEBO;
	GLuint VBOlightCube, VAOlightCube;
	GLuint VBOskybox, VAOskybox;

	GLuint texture1; //plane
	GLuint texture2; //object cube
	GLuint textureCubeMap;

	glm::vec3 pointLightPositions[4];

	Engine();
	~Engine();
	void init();
	void initPhysics();
	void initShape();
	void initShader();
	void initTexture();
	void initShadows();
	void run();
	void update(float frameDeltaTime);
	void processInput();
	void keyInput();
	void drawShape();
	void drawbox(Shader& shader);
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

inline SphereMesh generateSphere(float radius, unsigned int sectorCount, unsigned int stackCount)
{
	SphereMesh mesh;

	const float PI = 3.14159265359f;

	for (unsigned int i = 0; i <= stackCount; ++i)
	{
		float stackAngle = PI / 2 - i * (PI / stackCount); // from +pi/2 to -pi/2
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);

		for (unsigned int j = 0; j <= sectorCount; ++j)
		{
			float sectorAngle = j * (2 * PI / sectorCount); // from 0 to 2pi

			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);

			// Vertex position
			mesh.vertices.push_back(x);
			mesh.vertices.push_back(y);
			mesh.vertices.push_back(z);

			// Normalized normal
			float nx = x / radius;
			float ny = y / radius;
			float nz = z / radius;
			mesh.vertices.push_back(nx);
			mesh.vertices.push_back(ny);
			mesh.vertices.push_back(nz);

		}
	}

	// Generate indices
	for (unsigned int i = 0; i < stackCount; ++i)
	{
		for (unsigned int j = 0; j < sectorCount; ++j)
		{
			unsigned int first = i * (sectorCount + 1) + j;
			unsigned int second = first + sectorCount + 1;

			// Two triangles per quad
			mesh.indices.push_back(first);
			mesh.indices.push_back(second);
			mesh.indices.push_back(first + 1);

			mesh.indices.push_back(second);
			mesh.indices.push_back(second + 1);
			mesh.indices.push_back(first + 1);
		}
	}

	return mesh;
}

inline JPH::RVec3 generateRandomPosition()
{
	std::random_device rd;  // Random device for seed
	std::mt19937 gen(rd()); // Mersenne Twister generator

	//Uniform distribution in the range [0, windowSize - agentSize]
	std::uniform_real_distribution<float> distribution_x(0.f, 10.f);
	std::uniform_real_distribution<float> distribution_y(50.f, 100.f);
	std::uniform_real_distribution<float> distribution_z(0.f, 10.f);
	

	//world coordinates
	int x = distribution_x(gen);
	int y = distribution_y(gen);
	int z = distribution_z(gen);

	return JPH::RVec3(x, y, z);
}

inline unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}