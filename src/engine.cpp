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
    float vertices[] = {
        // FRONT face (-Z), top-down mapped (X-Z)
        -0.5f, -0.5f, -0.5f,  uMin, vMax,
         0.5f, -0.5f, -0.5f,  uMax, vMax,
         0.5f,  0.5f, -0.5f,  uMax, vMin,
         0.5f,  0.5f, -0.5f,  uMax, vMin,
        -0.5f,  0.5f, -0.5f,  uMin, vMin,
        -0.5f, -0.5f, -0.5f,  uMin, vMax,

        // BACK face (+Z), top-down mapped (X-Z)
        -0.5f, -0.5f,  0.5f,  uMin, vMax,
         0.5f, -0.5f,  0.5f,  uMax, vMax,
         0.5f,  0.5f,  0.5f,  uMax, vMin,
         0.5f,  0.5f,  0.5f,  uMax, vMin,
        -0.5f,  0.5f,  0.5f,  uMin, vMin,
        -0.5f, -0.5f,  0.5f,  uMin, vMax,

        // TOP face (+Y), standard top-down (X-Z)
        -0.5f,  0.5f, -0.5f,  uTopMin, vTopMax,
         0.5f,  0.5f, -0.5f,  uTopMax, vTopMax,
         0.5f,  0.5f,  0.5f,  uTopMax, vTopMin,
         0.5f,  0.5f,  0.5f,  uTopMax, vTopMin,
        -0.5f,  0.5f,  0.5f,  uTopMin, vTopMin,
        -0.5f,  0.5f, -0.5f,  uTopMin, vTopMax,

        // BOTTOM face (-Y), top-down mapped (X-Z)
        -0.5f, -0.5f, -0.5f,  uBottomMin, vBottomMax,
         0.5f, -0.5f, -0.5f,  uBottomMax, vBottomMax,
         0.5f, -0.5f,  0.5f,  uBottomMax, vBottomMin,
         0.5f, -0.5f,  0.5f,  uBottomMax, vBottomMin,
        -0.5f, -0.5f,  0.5f,  uBottomMin, vBottomMin,
        -0.5f, -0.5f, -0.5f,  uBottomMin, vBottomMax,

        // LEFT face (-X), top-down mapped (X-Z)
        -0.5f, -0.5f, -0.5f,  uMin, vMax,
        -0.5f, -0.5f,  0.5f,  uMax, vMax,
        -0.5f,  0.5f,  0.5f,  uMax, vMin,
        -0.5f,  0.5f,  0.5f,  uMax, vMin,
        -0.5f,  0.5f, -0.5f,  uMin, vMin,
        -0.5f, -0.5f, -0.5f,  uMin, vMax,

        // RIGHT face (+X), top-down mapped (X-Z)
         0.5f, -0.5f, -0.5f,  uMin, vMax,
         0.5f, -0.5f,  0.5f,  uMax, vMax,
         0.5f,  0.5f,  0.5f,  uMax, vMin,
         0.5f,  0.5f,  0.5f,  uMax, vMin,
         0.5f,  0.5f, -0.5f,  uMin, vMin,
         0.5f, -0.5f, -0.5f,  uMin, vMax,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Engine::initShader()
{
    shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
    shader.bind();
}

void Engine::initTexture()
{
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

    glUniform1i(shader.getUniform("texture1"), 0); // set the texture unit 0 to texture1
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

void Engine::drawTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
}

void Engine::drawShape()
{
    //projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(shader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // camera position, target position, up vector
    glUniformMatrix4fv(shader.getUniform("view"), 1, GL_FALSE, &view[0][0]);


    glBindVertexArray(VAO);
    for (uint16_t x = 0; x < cubeCount; x++)
    {
        for (uint16_t y = 0; y < cubeCount; y++)
        {
            for (uint16_t z = 0; z < cubeCount; z++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, y, z));
                glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
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


	drawTexture();
	drawShape();


    glfwSwapBuffers(window);
    glfwPollEvents();
}