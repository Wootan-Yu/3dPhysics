//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <openglDebug.h>
//#include <demoShaderLoader.h>
//#include <iostream>
//
//
//#define USE_GPU_ENGINE 0
//extern "C"
//{
//	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
//	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
//}
//
//
//static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//}
//
//int main()
//{
//
//
//
//
//	if (!glfwInit())
//		return -1;
//
//
//#pragma region report opengl errors to std
//	//enable opengl debugging output.
//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
//#pragma endregion
//
//
//	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //you might want to do this when testing the game for shipping
//
//
//	GLFWwindow *window = window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwSetKeyCallback(window, key_callback);
//
//	glfwMakeContextCurrent(window);
//	gladLoadGL();
//	glfwSwapInterval(1);
//
//
//#pragma region report opengl errors to std
//	glEnable(GL_DEBUG_OUTPUT);
//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//	glDebugMessageCallback(glDebugOutput, 0);
//	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//#pragma endregion
//
//	//shader loading example
//	Shader s;
//	s.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
//	s.bind();
//
//	while (!glfwWindowShouldClose(window))
//	{
//		int width = 0, height = 0;
//
//		glfwGetFramebufferSize(window, &width, &height);
//		glViewport(0, 0, width, height);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		//I'm using the old pipeline here just to test, you shouldn't learn this,
//		//Also It might not work on apple
//		glBegin(GL_TRIANGLES);
//		glColor3f(1, 0, 0);
//		glVertex2f(0,1);
//		glColor3f(0, 1, 0);
//		glVertex2f(1,-1);
//		glColor3f(0, 0, 1);
//		glVertex2f(-1,-1);
//		glEnd();
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	return 0;
//}


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <demoShaderLoader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1750;
const unsigned int SCR_HEIGHT = 980;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = 400, lastY = 300;
bool firstMouse = true; // if first mouse input, we don't want to calculate the offset
float yaw = -90.0f; // yaw is initialized to -90.0 degrees, to make the camera look down the negative z-axis initially
float pitch = 0.0f; // pitch is initialized to 0.0 degrees, so the camera doesn't look up or down initially

float fov = 45.0f; // field of view



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled by default)

    // build and compile our shader zprogram
    // ------------------------------------
    Shader shader;
    shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
    shader.bind();


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



    glm::vec3 cubePositions[] = {
        glm::vec3(-0.375f,  0.0f,  0.0f),
        glm::vec3(4.f, 5.f, -16.f),
        glm::vec3(-3.f, -2.25f, -2.5f),
        glm::vec3(-7.5f, -2.f, -12.25f),
        glm::vec3(2.f, -0.5f, -3.5f),
        glm::vec3(-3.5f, 3.f, -7.5f),
        glm::vec3(2.5f, -2.f, -2.5f),
        glm::vec3(3.f, 2.f, -2.5f),
        glm::vec3(3.f, 0.25f, -1.5f),
        glm::vec3(-2.5f, 1.f, -1.5f)
    };

    unsigned int VBO, VAO;
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


    // load and create a texture 
    // -------------------------
    unsigned int texture1;
    // texture 1
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



    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// hide the cursor and enable unlimited movement
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    float speed = 10.f;


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(window);


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        //projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(shader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // camera position, target position, up vector
        glUniformMatrix4fv(shader.getUniform("view"), 1, GL_FALSE, &view[0][0]);


        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = speed * (i + 1) * currentFrame;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		cameraPos.y += cameraSpeed; // move up
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		cameraPos.y -= cameraSpeed; // move down
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
