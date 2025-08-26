#include "engine.h"

Engine::Engine()
{
	init();
}

void Engine::init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#pragma region report opengl errors to std
	//enable opengl debugging output.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#pragma endregion

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled by default)


#pragma region report opengl errors to std
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, 0);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#pragma endregion
}

void Engine::initShape()
{
    float tileSize = 1.0f / 16.0f; // = 0.0625 (tileSize per texture)
    //side
    float sideTileX = 1; // column
    float sideTileY = 0; // row

    float uMin = sideTileX * tileSize;
    float vMin = sideTileY * tileSize;
    float uMax = uMin + tileSize;
    float vMax = vMin + tileSize;

    //top
    float topTileX = 0; // column
    float topTileY = 0; // row

    float uTopMin = topTileX * tileSize;
    float vTopMin = topTileY * tileSize;
    float uTopMax = uTopMin + tileSize;
    float vTopMax = vTopMin + tileSize;

    //bottom
    float bottomTileX = 2; // column
    float bottomTileY = 0; // row

    float uBottomMin = bottomTileX * tileSize;
    float vBottomMin = bottomTileY * tileSize;
    float uBottomMax = uBottomMin + tileSize;
    float vBottomMax = vBottomMin + tileSize;



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
        // FRONT face (-Z), top-down mapped (X-Z)
        -0.5f, -0.5f, -0.5f,  uMin, vMax, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  uMax, vMax, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  uMax, vMin, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  uMax, vMin, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  uMin, vMin, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  uMin, vMax, 0.0f,  0.0f, -1.0f,

        // BACK face (+Z), top-down mapped (X-Z)
        -0.5f, -0.5f,  0.5f,  uMin, vMax, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  uMax, vMax, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  uMax, vMin, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  uMax, vMin, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  uMin, vMin, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  uMin, vMax, 0.0f,  0.0f, 1.0f,

        // TOP face (+Y), standard top-down (X-Z)
        -0.5f,  0.5f, -0.5f,  uTopMin, vTopMax, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  uTopMax, vTopMax, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  uTopMax, vTopMin, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  uTopMax, vTopMin, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  uTopMin, vTopMin, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  uTopMin, vTopMax, 0.0f,  1.0f,  0.0f,

        // BOTTOM face (-Y), top-down mapped (X-Z)
        -0.5f, -0.5f, -0.5f,  uBottomMin, vBottomMax, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  uBottomMax, vBottomMax, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  uBottomMax, vBottomMin, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  uBottomMax, vBottomMin, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  uBottomMin, vBottomMin, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  uBottomMin, vBottomMax, 0.0f, -1.0f,  0.0f,

        // LEFT face (-X), top-down mapped (X-Z)
        -0.5f, -0.5f, -0.5f,  uMin, vMax, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  uMax, vMax, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  uMax, vMin, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  uMax, vMin, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  uMin, vMin, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  uMin, vMax, -1.0f,  0.0f,  0.0f,

        // RIGHT face (+X), top-down mapped (X-Z)
         0.5f, -0.5f, -0.5f,  uMin, vMax, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  uMax, vMax, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  uMax, vMin, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  uMax, vMin, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  uMin, vMin, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  uMin, vMax, 1.0f,  0.0f,  0.0f,
    };

    glGenVertexArrays(1, &VAOcube);
    glGenBuffers(1, &VBOcube);

    glBindVertexArray(VAOcube);

    glBindBuffer(GL_ARRAY_BUFFER, VBOcube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	// normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);




    float planeVertices[] = {
		// positions          // texture    // normals
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top left 
    };

	unsigned int planeIndices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

    GLuint EBO;

	glGenVertexArrays(1, &VAOplane);
	glGenBuffers(1, &VBOplane);

	glBindVertexArray(VAOplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBOplane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);
    
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);




    float lightCubeVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    //light source
	glGenVertexArrays(1, &VAOlightCube);
    glGenBuffers(1, &VBOlightCube);

	glBindVertexArray(VAOlightCube);

	glBindBuffer(GL_ARRAY_BUFFER, VBOlightCube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightCubeVertices), lightCubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


    //object cube
	glGenVertexArrays(1, &VAOobject);
	glBindVertexArray(VAOobject);
	glBindBuffer(GL_ARRAY_BUFFER, VBOlightCube); // reuse the cube VBO
    //position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    //normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


}

void Engine::initShader()
{
    shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
	lightCubeShader.loadShaderProgramFromFile(RESOURCES_PATH "lightCubeVertex.vert", RESOURCES_PATH "lightCubeFrag.frag");
	objectShader.loadShaderProgramFromFile(RESOURCES_PATH "objectVertex.vert", RESOURCES_PATH "objectFrag.frag");
}

void Engine::initTexture()
{
	//blocks texture
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(RESOURCES_PATH "blocks.png", &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true); // must come before stbi_load
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }



    //plane texture
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load texture image
    int width2, height2, nrChannels2;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data2 = stbi_load(RESOURCES_PATH "wall.jpg", &width2, &height2, &nrChannels2, 0);
    if (data2)
    {
        GLenum format = (nrChannels2 == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width2, height2, 0, format, GL_UNSIGNED_BYTE, data2);
        stbi_image_free(data2);
    }
    else
    {
        std::cout << "Failed to load second texture: " << stbi_failure_reason() << std::endl;
    }



    //cube texture
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);

    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load texture image
    int width3, height3, nrChannels3;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data3 = stbi_load(RESOURCES_PATH "container2.png", &width3, &height3, &nrChannels3, 0);
    if (data3)
    {
        GLenum format = (nrChannels3 == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width3, height3, 0, format, GL_UNSIGNED_BYTE, data3);
        stbi_image_free(data3);
    }
    else
    {
        std::cout << "Failed to load second texture: " << stbi_failure_reason() << std::endl;
    }




    //cube texture
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);

    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load texture image
    int width4, height4, nrChannels4;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data4 = stbi_load(RESOURCES_PATH "container2_specular.png", &width4, &height4, &nrChannels4, 0);
    if (data4)
    {
        GLenum format = (nrChannels4 == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width4, height4, 0, format, GL_UNSIGNED_BYTE, data4);
        stbi_image_free(data4);
    }
    else
    {
        std::cout << "Failed to load second texture: " << stbi_failure_reason() << std::endl;
    }
}

void Engine::run()
{
    initShape();
    initShader();
    initTexture();
	processInput(); //mouse, cursor and scroll input
    while (!glfwWindowShouldClose(window))
    {
        keyInput(); //key input
		update();
		render();
	}
}

void Engine::processInput()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// hide the cursor and enable unlimited movement
    glfwSetCursorPosCallback(window, UserInput::mouse_callback);
    glfwSetScrollCallback(window, UserInput::scroll_callback);
}

void Engine::keyInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront; // move forward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront; // move backward
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; // move left
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; // move right
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        cameraPos.y += cameraSpeed; // move up
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        cameraPos.y -= cameraSpeed; // move down
}

void Engine::update()
{

}

void Engine::drawShape()
{
    float time = glfwGetTime(); // seconds since program start
    float radius = 5.0f;

    shader.bind();
    //projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(shader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // camera position, target position, up vector
    glUniformMatrix4fv(shader.getUniform("view"), 1, GL_FALSE, &view[0][0]);


    //material
    glm::vec3 materialAmbient(0.5f, 0.5f, 0.5f);
    glm::vec3 materialDiffuse(0.5f, 0.5f, 0.5f);
    glm::vec3 materialSpecular(0.5f, 0.5f, 0.5f);
    float objectShininess = 32; //2, 4, 8, 16, 32, 64, 128, 256 (shine level)
    //light
    glm::vec3 lightAmbient(0.2f, 0.2f, 0.2f);
    glm::vec3 lightDiffuse(0.5f, 0.5f, 0.5f);
    glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos(0.f, 3.0f, 0.f);

    lightPos.x = sin(time) * radius;
    lightPos.y = 3.0f; // fixed height
    lightPos.z = cos(time) * radius;

	//cubes
    glUniform1i(shader.getUniform("choice"), 0); // set the texture unit 0 to texture1
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(shader.getUniform("texture1"), 0); // set the texture unit 0 to texture1

    glBindVertexArray(VAOcube);
    /*for (uint16_t x = 0; x < cubeCount; x++)
    {
        for (uint16_t y = 0; y < cubeCount; y++)
        {
            for (uint16_t z = 0; z < cubeCount; z++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, y + 0.51f, z));
				glUniform3f(shader.getUniform("lightColor"), lightColor[0], lightColor[1], lightColor[2]);
                glUniform3fv(shader.getUniform("lightposition"), 1, &lightPos[0]);
                glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }*/

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, 0.51f, 0.f));
    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
    glUniform3fv(shader.getUniform("lightPosition"), 1, &lightPos[0]);
	glUniform3fv(shader.getUniform("viewPosition"), 1, &cameraPos[0]);
    
    glUniform3fv(shader.getUniform("material.ambient"), 1, &materialAmbient[0]);
    glUniform3fv(shader.getUniform("material.diffuse"), 1, &materialDiffuse[0]);
    glUniform3fv(shader.getUniform("material.specular"), 1, &materialSpecular[0]);
    glUniform1f(shader.getUniform("material.shininess"), objectShininess);

    glUniform3fv(shader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(shader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(shader.getUniform("light.specular"), 1, &lightSpecular[0]);
	
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    

    //plane
    glUniform1i(shader.getUniform("choice"), 1); // set the texture unit 0 to texture1
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(shader.getUniform("texture2"), 1); // set the texture unit 1 to texture2

	glBindVertexArray(VAOplane);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(shader.getUniform("lightPosition"), 1, &lightPos[0]);
    glUniform3fv(shader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform3fv(shader.getUniform("material.ambient"), 1, &materialAmbient[0]);
    glUniform3fv(shader.getUniform("material.diffuse"), 1, &materialDiffuse[0]);
    glUniform3fv(shader.getUniform("material.specular"), 1, &materialSpecular[0]);
    glUniform1f(shader.getUniform("material.shininess"), objectShininess);

    glUniform3fv(shader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(shader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(shader.getUniform("light.specular"), 1, &lightSpecular[0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



    //light source
    lightCubeShader.bind();
    glUniformMatrix4fv(lightCubeShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(lightCubeShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);
	
	glBindVertexArray(VAOlightCube);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	glUniformMatrix4fv(lightCubeShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);





    //material
    materialAmbient = glm::vec3(1.0f, 0.5f, 0.31f);
    materialDiffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    materialSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
    objectShininess = 32; //2, 4, 8, 16, 32, 64, 128, 256 (shine level)

    //light
    lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    lightSpecular = glm::vec3(1.f);

	//object
	glm::vec3 objectPos(2.f, 0.51f, 0.f);
	

	objectShader.bind();
	glUniformMatrix4fv(objectShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(objectShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texture4);

	glBindVertexArray(VAOobject);
    model = glm::mat4(1.0f);
    model = glm::translate(model, objectPos);
    glUniformMatrix4fv(objectShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(objectShader.getUniform("lightPosition"), 1, &lightPos[0]);
	glUniform3fv(objectShader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform1i(objectShader.getUniform("material.diffuse"), 2); //texture 3 = 2
    glUniform1i(objectShader.getUniform("material.specular"), 3); //texture 4 = 3
    glUniform1f(objectShader.getUniform("material.shininess"), objectShininess);

	glUniform3fv(objectShader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(objectShader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(objectShader.getUniform("light.specular"), 1, &lightSpecular[0]);

    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Engine::render() 
{
	//deltaTime calculation
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;



    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	drawShape();


    glfwSwapBuffers(window);
    glfwPollEvents();
}