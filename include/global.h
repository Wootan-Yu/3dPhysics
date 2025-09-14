#pragma once

#include <glm/glm.hpp>

inline const int cubeCount = 3;
inline glm::vec3 cubePositions[cubeCount];
inline float rotationFactors[cubeCount];

// settings
inline const unsigned int SCR_WIDTH = 1750;
inline const unsigned int SCR_HEIGHT = 980;

inline glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 20.0f);  // -0.0187399f, 2.27462f, 20.4832f
inline glm::vec3 cameraFront = glm::vec3(0.0f, -0.2f, -1.0f);
inline glm::vec3 cameraUp = glm::vec3(0.0f, 1.f, 0.0f);

inline float deltaTime = 0.0f;	// Time between current frame and last frame
inline float lastFrame = 0.0f; // Time of last frame

inline float lastX = 400, lastY = 300;
inline bool firstMouse = true; // if first mouse input, we don't want to calculate the offset
inline float yaw = -90.0f; // yaw is initialized to -90.0 degrees, to make the camera look down the negative z-axis initially
inline float pitch = 0.0f; // pitch is initialized to 0.0 degrees, so the camera doesn't look up or down initially

inline float fov = 45.0f; // field of view

inline float speed = 150.f; // camera speed


inline unsigned int amount = 1; //no. of spheres
inline float radius = 1.f;
inline float offset = 25.f;


inline const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//inline const glm::vec3 lightPos(0.0f, 5.0f, 0.0f);
inline const glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);


inline glm::mat4 view;
inline glm::mat4 projection;

inline glm::mat4 lightProjection, lightView;
inline glm::mat4 lightSpaceMatrix;
