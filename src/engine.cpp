#include "engine.h"

Engine::Engine()
{
	init();
}

Engine::~Engine()
{
    glDeleteVertexArrays(1, &VAOskybox);
    glDeleteBuffers(1, &VBOskybox);
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
    glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB); //enable gamma correction

#pragma region report opengl errors to std
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, 0);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#pragma endregion
}

void Engine::initShape()
{
    /*
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
    */



    
    float planeVertices[] = {
		 // positions          // texture    // normals
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top left 
    };

    unsigned int planeIndices[] = {
        0, 3, 1,   // first triangle
        1, 3, 2    // second triangle
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
    




    /*
    float lightCubeVertices[] = {
        // positions          // normals           // texture coords

        // FRONT face (-Z)
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Vertex 1
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // Vertex 2
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // Vertex 3
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // Vertex 4
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // Vertex 5
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Vertex 6

        // BACK face (+Z)
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f, // Vertex 1
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f, // Vertex 2
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f, // Vertex 3
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f, // Vertex 4
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f, // Vertex 5
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f, // Vertex 6

        // LEFT face (-X)
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Vertex 1
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Vertex 2
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Vertex 3
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Vertex 4
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Vertex 5
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Vertex 6

        // RIGHT face (+X)
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Vertex 1
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Vertex 2
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Vertex 3
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Vertex 4
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Vertex 5
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Vertex 6

         // BOTTOM face (-Y)
         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // Vertex 1
          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // Vertex 2
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // Vertex 3
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // Vertex 4
         -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // Vertex 5
         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // Vertex 6

         // TOP face (+Y)
         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Vertex 1
          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // Vertex 2
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // Vertex 3
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // Vertex 4
         -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // Vertex 5
         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f  // Vertex 6
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
    */




    //skybox cube
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    glGenVertexArrays(1, &VAOskybox);
    glGenBuffers(1, &VBOskybox);

    glBindVertexArray(VAOskybox);
    glBindBuffer(GL_ARRAY_BUFFER, VBOskybox);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    // position only, no other attributes, stride is 3 floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    //guitarBackpackModel.loadModel(RESOURCES_PATH "guitar_backpack/backpack.obj");
    //sponzaModel.loadModel(RESOURCES_PATH "Sponza/glTF/Sponza.gltf");
    spaceHelmetModel.loadModel_gltf(RESOURCES_PATH "space_helmet/scene.gltf");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void Engine::initShader()
{
    shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
	//lightCubeShader.loadShaderProgramFromFile(RESOURCES_PATH "lightCubeVertex.vert", RESOURCES_PATH "lightCubeFrag.frag");
	//objectShader.loadShaderProgramFromFile(RESOURCES_PATH "objectVertex.vert", RESOURCES_PATH "objectFrag.frag");
    //guitarBackpackShader.loadShaderProgramFromFile(RESOURCES_PATH "guitar_backpack/modelLoadvert.vert", RESOURCES_PATH "guitar_backpack/modelLoadfrag.frag");
    //sponzaShader.loadShaderProgramFromFile(RESOURCES_PATH "Sponza/modelVert.vert", RESOURCES_PATH "Sponza/modelFrag.frag");
    spaceHelmetShader.loadShaderProgramFromFile(RESOURCES_PATH "space_helmet/modelVert.vert", RESOURCES_PATH "space_helmet/modelFrag.frag");
    skyboxShader.loadShaderProgramFromFile(RESOURCES_PATH "skybox/vertShader.vert", RESOURCES_PATH "skybox/fragShader.frag");
}

void Engine::initTexture()
{
    /*
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
    */


    
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
    unsigned char* data2 = stbi_load(RESOURCES_PATH "wood.png", &width2, &height2, &nrChannels2, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        stbi_image_free(data2);
    }
    else
    {
        std::cout << "Failed to load second texture: " << stbi_failure_reason() << std::endl;
    }
    
    


    /*
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
    */


    /*
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
    */
    
    std::string directory = "C:/Users/Wootan/Desktop/github_files/Wootan-Yu/3dPhysics/resources/skybox/";

    //cube map texture
    std::vector<std::string> faces
    {
        directory + "right.jpg",
        directory + "left.jpg",
        directory + "top.jpg",
        directory + "bottom.jpg",
        directory + "front.jpg",
        directory + "back.jpg"
    };

    textureCubeMap = loadCubemap(faces);
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

    //std::cout << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << '\n';
}

void Engine::update()
{

}

void Engine::drawShape()
{
    
    //float time = glfwGetTime(); // seconds since program start
    //static float radius = 5.0f;

    //shader.bind();
    //projection matrix
    //glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    //glUniformMatrix4fv(shader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

    //glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // camera position, target position, up vector
    //glUniformMatrix4fv(shader.getUniform("view"), 1, GL_FALSE, &view[0][0]);
    

    /*
	//cubes
    glUniform1i(shader.getUniform("choice"), 0); // set the bool to 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(shader.getUniform("texture1"), 0); // set the texture unit 0 to texture1

    glBindVertexArray(VAOcube);
    */


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

    /*
    static glm::mat4 model = glm::mat4(1.0f);
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
    */

    
    //material
    static glm::vec3 materialAmbient(0.5f, 0.5f, 0.5f);
    static glm::vec3 materialDiffuse(0.5f, 0.5f, 0.5f);
    static glm::vec3 materialSpecular(1.f, 1.f, 1.f);
    static float objectShininess = 32; //2, 4, 8, 16, 32, 64, 128, 256 (shine level)
    //light
    static glm::vec3 lightAmbient(0.2f, 0.2f, 0.2f);
    static glm::vec3 lightDiffuse(1.0f, 1.0f, 0.6f); // brighter yellow
    static glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);

    static glm::vec3 lightPos(0.f, 3.0f, 0.f);

    //plane
    shader.bind();
    //projection matrix
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // camera position, target position, up vector
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 45.0f);
    

    glUniformMatrix4fv(shader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(shader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    glUniform1i(shader.getUniform("choice"), 1); //set the bool to 1
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(shader.getUniform("texture2"), 1); // set the texture unit 1 to texture2

	glBindVertexArray(VAOplane);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, -4.f, 0.f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));
	
    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(shader.getUniform("light.position"), 1, &lightPos[0]);
    glUniform3fv(shader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform3fv(shader.getUniform("material.ambient"), 1, &materialAmbient[0]);
    glUniform3fv(shader.getUniform("material.diffuse"), 1, &materialDiffuse[0]);
    glUniform3fv(shader.getUniform("material.specular"), 1, &materialSpecular[0]);
    glUniform1f(shader.getUniform("material.shininess"), objectShininess);

    glUniform3fv(shader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(shader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(shader.getUniform("light.specular"), 1, &lightSpecular[0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    

    
    /*glm::mat4 model(1.0f);

    static const glm::vec3 pointLightPositions[4] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };


    // positions all containers
    static const glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightColors[] = {
    glm::vec3(1.0f, 0.5f, 0.0f), // Orange
    glm::vec3(1.0f, 0.0f, 0.0f), // Red
    glm::vec3(0.0f, 1.0f, 0.0f), // Green
    glm::vec3(0.0f, 0.0f, 1.0f)  // Blue
    };

    //light source
    lightCubeShader.bind();
    glUniformMatrix4fv(lightCubeShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(lightCubeShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);
	
	glBindVertexArray(VAOlightCube);
    for (uint8_t i = 0; i < 4; i++) //these are for the 4 random lights
    {
        model = glm::mat4(1.0f);
	    model = glm::translate(model, pointLightPositions[i]);
	    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        glUniform3fv(lightCubeShader.getUniform("color"), 1, &pointLightColors[i][0]);
	    glUniformMatrix4fv(lightCubeShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
	    glDrawArrays(GL_TRIANGLES, 0, 36);
    }
	




    //material
    materialDiffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    materialSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
    objectShininess = 32; //2, 4, 8, 16, 32, 64, 128, 256 (shine level)

    static float constant = 1.f;
    static float linear = 0.09f;
    static float quadratic = 0.032f;

	//object
    static glm::vec3 objectPos(2.f, 0.51f, 0.f);
	

	objectShader.bind();
	glUniformMatrix4fv(objectShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(objectShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texture4);

	glBindVertexArray(VAOobject);
    
	glUniform3fv(objectShader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform1i(objectShader.getUniform("material.diffuse"), 2); //texture 3 = 2
    glUniform1i(objectShader.getUniform("material.specular"), 3); //texture 4 = 3
    glUniform1f(objectShader.getUniform("material.shininess"), objectShininess);

    glUniform3f(objectShader.getUniform("dirLight.direction"), -0.2f, -1.0f, -0.3f);
    glUniform3f(objectShader.getUniform("dirLight.ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(objectShader.getUniform("dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    glUniform3f(objectShader.getUniform("dirLight.specular"), 0.5f, 0.5f, 0.5f);

    // Orange light
    glUniform3fv(objectShader.getUniform("pointLights[0].position"), 1, &pointLightPositions[0][0]);
    glUniform3f(objectShader.getUniform("pointLights[0].ambient"), 0.05f, 0.025f, 0.0f);
    glUniform3f(objectShader.getUniform("pointLights[0].diffuse"), 1.0f, 0.5f, 0.0f);
    glUniform3f(objectShader.getUniform("pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[0].constant"), 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[0].linear"), 0.09f);
    glUniform1f(objectShader.getUniform("pointLights[0].quadratic"), 0.032f);

    // Red light
    glUniform3fv(objectShader.getUniform("pointLights[1].position"), 1, &pointLightPositions[1][0]);
    glUniform3f(objectShader.getUniform("pointLights[1].ambient"), 0.05f, 0.01f, 0.01f);
    glUniform3f(objectShader.getUniform("pointLights[1].diffuse"), 1.0f, 0.0f, 0.0f);
    glUniform3f(objectShader.getUniform("pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[1].constant"), 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[1].linear"), 0.09f);
    glUniform1f(objectShader.getUniform("pointLights[1].quadratic"), 0.032f);

    // Green light
    glUniform3fv(objectShader.getUniform("pointLights[2].position"), 1, &pointLightPositions[2][0]);
    glUniform3f(objectShader.getUniform("pointLights[2].ambient"), 0.01f, 0.05f, 0.01f);
    glUniform3f(objectShader.getUniform("pointLights[2].diffuse"), 0.0f, 1.0f, 0.0f);
    glUniform3f(objectShader.getUniform("pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[2].constant"), 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[2].linear"), 0.09f);
    glUniform1f(objectShader.getUniform("pointLights[2].quadratic"), 0.032f);

    // Blue light
    glUniform3fv(objectShader.getUniform("pointLights[3].position"), 1, &pointLightPositions[3][0]);
    glUniform3f(objectShader.getUniform("pointLights[3].ambient"), 0.01f, 0.01f, 0.05f);
    glUniform3f(objectShader.getUniform("pointLights[3].diffuse"), 0.0f, 0.0f, 1.0f);
    glUniform3f(objectShader.getUniform("pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[3].constant"), 1.0f);
    glUniform1f(objectShader.getUniform("pointLights[3].linear"), 0.09f);
    glUniform1f(objectShader.getUniform("pointLights[3].quadratic"), 0.032f);


    glUniform3fv(objectShader.getUniform("spotLight.position"), 1, &cameraPos[0]);
    glUniform3fv(objectShader.getUniform("spotLight.direction"), 1, &cameraFront[0]);
    glUniform3f(objectShader.getUniform("spotLight.ambient"), 0.0f, 0.0f, 0.0f);
    glUniform3f(objectShader.getUniform("spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
    glUniform3f(objectShader.getUniform("spotLight.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(objectShader.getUniform("spotLight.constant"), 1.0f);
    glUniform1f(objectShader.getUniform("spotLight.linear"), 0.09f);
    glUniform1f(objectShader.getUniform("spotLight.quadratic"), 0.032f);
    glUniform1f(objectShader.getUniform("spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
    glUniform1f(objectShader.getUniform("spotLight.outerCutOff"), glm::cos(glm::radians(12.5f)));

    for (uint8_t i = 0; i < 10; i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(objectShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    */
    


    /*
    guitarBackpackShader.bind();
    // Setup view and projection for modelShader
    glUniformMatrix4fv(guitarBackpackShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(guitarBackpackShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    // Model matrix for the .obj model
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f)); // scale down if too big
    glUniformMatrix4fv(guitarBackpackShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
    
    guitarBackpackModel.Draw(guitarBackpackShader);
    */

    /*
    sponzaShader.bind();
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(sponzaShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // camera position, target position, up vector
    glUniformMatrix4fv(sponzaShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    // Model matrix for the .obj model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.03f)); // scale down if too big
    glUniformMatrix4fv(sponzaShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);

    sponzaModel.Draw(sponzaShader);
    */




    

    static glm::vec3 helmetMaterialAmbient(1.0f);
    static glm::vec3 helmetMaterialDiffuse = glm::vec3(1.0f);
    static glm::vec3 helmetMaterialSpecular = glm::vec3(0.2);
    static float helmetObjectShininess = 128; //2, 4, 8, 16, 32, 64, 128, 256 (shine level)

    //light
    static glm::vec3 helmetLightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    static glm::vec3 helmetLightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    static glm::vec3 helmetLightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

    static glm::vec3 helmetLightPos = glm::vec3(0.f, 3.0f, 0.f);

    spaceHelmetShader.bind();
    
    glUniformMatrix4fv(spaceHelmetShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(spaceHelmetShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    // Model matrix for the .obj model
    glm::mat4 modelHelm = glm::mat4(1.0f);
    modelHelm = glm::rotate(modelHelm, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    modelHelm = glm::translate(modelHelm, glm::vec3(0.0f, 0.0f, 0.0f));
    modelHelm = glm::scale(modelHelm, glm::vec3(3.f)); // scale down if too big
    glUniformMatrix4fv(spaceHelmetShader.getUniform("model"), 1, GL_FALSE, &modelHelm[0][0]);
    
    
    glUniform3fv(spaceHelmetShader.getUniform("viewPosition"), 1, &cameraPos[0]);
    glUniform3fv(spaceHelmetShader.getUniform("light.position"), 1, &helmetLightPos[0]);

    glUniform3fv(spaceHelmetShader.getUniform("material.ambient"), 1, &helmetMaterialAmbient[0]);
    glUniform3fv(spaceHelmetShader.getUniform("material.diffuse"), 1, &helmetMaterialDiffuse[0]);
    glUniform3fv(spaceHelmetShader.getUniform("material.specular"), 1, &helmetMaterialSpecular[0]);
    glUniform1f(spaceHelmetShader.getUniform("material.shininess"), helmetObjectShininess);

    glUniform3fv(spaceHelmetShader.getUniform("light.ambient"), 1, &helmetLightAmbient[0]);
    glUniform3fv(spaceHelmetShader.getUniform("light.diffuse"), 1, &helmetLightDiffuse[0]);
    glUniform3fv(spaceHelmetShader.getUniform("light.specular"), 1, &helmetLightSpecular[0]);


    spaceHelmetModel.Draw(spaceHelmetShader);
    





    //note: to give us a slight performance boost we're going to render the skybox LAST. 
    // This way, the depth buffer is completely filled with all the scene's depth values 
    // so we only have to render the skybox's fragments wherever the early depth test passes, 
    // greatly reducing the number of fragment shader calls.


    glDepthFunc(GL_LEQUAL);  // Use "less than or equal" instead of default "less than" 

    skyboxShader.bind();
    glBindVertexArray(VAOskybox);
    glDepthMask(GL_FALSE); // Don't write to depth buffer (skybox should always be in background)

    glUniformMatrix4fv(skyboxShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

    //MUST remove translation from camera view
    //If you use full glm::lookAt(...), the skybox cube will "move" and appear small
    glm::mat4 skyboxView = glm::mat4(glm::mat3(view)); 
    glUniformMatrix4fv(skyboxShader.getUniform("view"), 1, GL_FALSE, &skyboxView[0][0]);

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureCubeMap);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);   // Re-enable depth writing
    glDepthFunc(GL_LESS);   // Restore default depth function

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