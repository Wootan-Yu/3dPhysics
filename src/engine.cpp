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

    GLuint planeEBO;

	glGenVertexArrays(1, &VAOplane);
	glGenBuffers(1, &VBOplane);

	glBindVertexArray(VAOplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBOplane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);


	glGenBuffers(1, &planeEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);
 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    




    float physicsCubeVertices[] = {
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
         // Bottom face
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
         // Top face
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
    };

    unsigned int VBOPhysicsCube;

    glGenVertexArrays(1, &VAOPhysicsCube);
    glGenBuffers(1, &VBOPhysicsCube);

    glBindVertexArray(VAOPhysicsCube);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOPhysicsCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(physicsCubeVertices), physicsCubeVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    //physics cube wireframe
    float cubeEdges[] = {
        // Bottom face edges
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,
         
        // Top face edges
        -0.5f,  0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f,

        // Vertical edges
        -0.5f, -0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
    };

    unsigned int VBOOutline;
    glGenVertexArrays(1, &VAOOutline);
    glGenBuffers(1, &VBOOutline);

    glBindVertexArray(VAOOutline);
    glBindBuffer(GL_ARRAY_BUFFER, VBOOutline);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeEdges), cubeEdges, GL_STATIC_DRAW);

    // position only
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    
    //sphere
    sphereObject = generateSphere(1.0f, 64, 32); // radius = 1.0, resolution

    GLuint VBOsphere, EBOsphere;
    glGenVertexArrays(1, &VAOsphere);
    glGenBuffers(1, &VBOsphere);
    glGenBuffers(1, &EBOsphere);

    glBindVertexArray(VAOsphere);

    glBindBuffer(GL_ARRAY_BUFFER, VBOsphere);
    glBufferData(GL_ARRAY_BUFFER, sphereObject.vertices.size() * sizeof(float), sphereObject.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOsphere);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereObject.indices.size() * sizeof(unsigned int), sphereObject.indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    



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
}

void Engine::initPhysics()
{
    // 1) Basic allocator + factory
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();

    // 2) Register Jolt built-in types (CRITICAL)
    JPH::RegisterTypes();

    // 4) Layer/filter objects (keep these alive for lifetime of physicsSystem)
    static BPLayerInterfaceImpl broadPhaseLayerInterface;
    static ObjectVsBroadPhaseLayerFilterImpl objVsBpFilter;
    static ObjectLayerPairFilterImpl objPairFilter;

    // 5) Init physics system
    physicsSystem.Init(
        1024, // max bodies
        0,    // num body mutexes
        1024, // max body pairs
        1024, // max contacts
        broadPhaseLayerInterface,
        objVsBpFilter,
        objPairFilter);

    // 6) Store body interface
    bodyInterface = &physicsSystem.GetBodyInterface();
    physicsSystem.SetGravity(JPH::Vec3(0, -2.f, 0)); // gentle gravity


    //sphere
    JPH::SphereShapeSettings sphereSettings(1.0);
    JPH::ShapeRefC sphereShape = sphereSettings.Create().Get();

    JPH::BodyCreationSettings ballSettings(
        sphereShape,
        JPH::RVec3(0.f, 15.f, 0.f),
        JPH::Quat::sIdentity(),
        JPH::EMotionType::Dynamic,           // movable body
        Layers::MOVING                       // your object layer
    );

    ballSettings.mMassPropertiesOverride.mMass = 10.f; // lighter = falls slower (but still gravity applies)
    ballSettings.mLinearDamping = 0.9f; // slows velocity each tick
    ballSettings.mRestitution = 1.f;

    sphereBodyID = bodyInterface->CreateAndAddBody(ballSettings, JPH::EActivation::Activate);



    //cube
    JPH::BoxShapeSettings boxSettings(JPH::Vec3(0.5f, 0.5f, 0.5f)); // 1x1x1 cube
    JPH::ShapeRefC cubeShape = boxSettings.Create().Get();

    JPH::BodyCreationSettings cubeSettings(
        cubeShape,
        JPH::RVec3(0.0f, 20.0f, 0.0f),        // <-- initial position (y = 5 units above ground)
        JPH::Quat::sIdentity(),              // no rotation
        JPH::EMotionType::Dynamic,           // movable body
        Layers::MOVING                       // your object layer
    );

    cubeSettings.mMotionType = JPH::EMotionType::Dynamic;
    cubeSettings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
    cubeSettings.mMassPropertiesOverride.mMass = 5.f; // lighter = falls slower (but still gravity applies)
    cubeSettings.mLinearDamping = 0.9f; // slows velocity each tick
    cubeSettings.mRestitution = 0.8f;

    cubeBodyID = bodyInterface->CreateAndAddBody(cubeSettings, JPH::EActivation::Activate);



    //plane
    // Create an infinite plane (normal pointing up, passing through origin)
    JPH::Plane plane(JPH::Vec3(0, 1, 0), 0.0f);
    JPH::PlaneShapeSettings planeSettings(plane); // y=0 plane

    // Create the shape
    JPH::ShapeRefC planeShape = planeSettings.Create().Get();

    JPH::BodyCreationSettings floorSettings(
        planeShape,
        JPH::RVec3::sZero(),                  // at origin
        JPH::Quat::sIdentity(),
        JPH::EMotionType::Static,             // immovable
        Layers::NON_MOVING
    );

    JPH::BodyID floorID = bodyInterface->CreateAndAddBody(floorSettings, JPH::EActivation::DontActivate);
}

void Engine::initShader()
{
    shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
    physicsCubeShader.loadShaderProgramFromFile(RESOURCES_PATH "physicsCubeVert.vert", RESOURCES_PATH "physicsCubeFrag.frag");
    outlineShader.loadShaderProgramFromFile(RESOURCES_PATH "outlineVert.vert", RESOURCES_PATH "outlineFrag.frag");
    sphereShader.loadShaderProgramFromFile(RESOURCES_PATH "sphereVert.vert", RESOURCES_PATH "sphereFrag.frag");
    //lightCubeShader.loadShaderProgramFromFile(RESOURCES_PATH "lightCubeVertex.vert", RESOURCES_PATH "lightCubeFrag.frag");
	//objectShader.loadShaderProgramFromFile(RESOURCES_PATH "objectVertex.vert", RESOURCES_PATH "objectFrag.frag");
    //guitarBackpackShader.loadShaderProgramFromFile(RESOURCES_PATH "guitar_backpack/modelLoadvert.vert", RESOURCES_PATH "guitar_backpack/modelLoadfrag.frag");
    //sponzaShader.loadShaderProgramFromFile(RESOURCES_PATH "Sponza/modelVert.vert", RESOURCES_PATH "Sponza/modelFrag.frag");
    //spaceHelmetShader.loadShaderProgramFromFile(RESOURCES_PATH "space_helmet/modelVert.vert", RESOURCES_PATH "space_helmet/modelFrag.frag");
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
        GLenum internalFormat = (nrChannels3 == 4) ? GL_SRGB_ALPHA : GL_SRGB;
        GLenum dataFormat = (nrChannels3 == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width3, height3, 0, dataFormat, GL_UNSIGNED_BYTE, data3);
    }
    else
    {
        std::cout << "Failed to load second texture: " << stbi_failure_reason() << std::endl;
    }
    


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
    }*/
    
    
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
    initPhysics(); //physics
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
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        // Move cube back to (0, 20, 0) with no rotation, zero velocity
        bodyInterface->SetPositionAndRotation(
            cubeBodyID,
            JPH::RVec3(0.0f, 20.0f, 0.0f),
            JPH::Quat::sIdentity(),
            JPH::EActivation::Activate
        );
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        // Move cube back to (0, 20, 0) with no rotation, zero velocity
        bodyInterface->SetPositionAndRotation(
            sphereBodyID,
            JPH::RVec3(0.0f, 15.0f, 0.0f),
            JPH::Quat::sIdentity(),
            JPH::EActivation::Activate
        );
    }


    //std::cout << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << '\n';
}

void Engine::update()
{
    // Create temporary memory allocator and job system
    static JPH::TempAllocatorImpl tempAllocator(10 * 1024 * 1024);
    static JPH::JobSystemThreadPool jobSystem(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);

    // Step physics
    physicsSystem.Update(1.0f / 60.0f, 1, &tempAllocator, &jobSystem);

    // Fetch cube transform
    JPH::RMat44 cube = bodyInterface->GetCenterOfMassTransform(cubeBodyID);
    cube.StoreFloat4x4((JPH::Float4*)cubeMat);  // reinterpret as float[16]
    cubeModel = glm::make_mat4(cubeMat);

    JPH::RMat44 sphere = bodyInterface->GetCenterOfMassTransform(sphereBodyID);
    sphere.StoreFloat4x4((JPH::Float4*)sphereMat);
    sphereModel = glm::make_mat4(sphereMat);
}

void Engine::drawShape()
{
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
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
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
    

    


    //physics cubes
    physicsCubeShader.bind();
    glUniformMatrix4fv(physicsCubeShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(physicsCubeShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);


    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glUniform1i(physicsCubeShader.getUniform("texture1"), 2); // set the texture unit 0 to texture1

    
    //outline
    outlineShader.bind();
    glUniformMatrix4fv(outlineShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(outlineShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    static glm::vec3 lineColor(1.f, 1.f, 1.f);


    // 1. Draw solid cube
    physicsCubeShader.bind();
    glBindVertexArray(VAOPhysicsCube);
    glUniformMatrix4fv(physicsCubeShader.getUniform("model"), 1, GL_FALSE, &cubeModel[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // 2. Draw outline
    outlineShader.bind();
    glBindVertexArray(VAOOutline);
    glUniformMatrix4fv(outlineShader.getUniform("model"), 1, GL_FALSE, &cubeModel[0][0]);
    glUniform3fv(outlineShader.getUniform("lineColor"), 1, &lineColor[0]);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 24);

    /*
    for (uint16_t x = 0; x < cubeCount; x++)
    {
        for (uint16_t y = 0; y < cubeCount; y++)
        {
            for (uint16_t z = 0; z < cubeCount; z++)
            {
                // 1. Draw solid cube
                physicsCubeShader.bind();
                glBindVertexArray(VAOPhysicsCube);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, y + 0.51f, z));
                glUniformMatrix4fv(physicsCubeShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                // 2. Draw outline
                outlineShader.bind();
                glBindVertexArray(VAOOutline);
                glUniformMatrix4fv(outlineShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
                glUniform3fv(outlineShader.getUniform("lineColor"), 1, &lineColor[0]);
                glLineWidth(2.0f);
                glDrawArrays(GL_LINES, 0, 24);
            }
        }
    }*/



    //sphere
    sphereShader.bind();
    glUniformMatrix4fv(sphereShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(sphereShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);


    glBindVertexArray(VAOsphere);
    glUniformMatrix4fv(sphereShader.getUniform("model"), 1, GL_FALSE, &sphereModel[0][0]);
    glUniform3fv(sphereShader.getUniform("light.position"), 1, &lightPos[0]);
    glUniform3fv(sphereShader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform3f(sphereShader.getUniform("material.ambient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(sphereShader.getUniform("material.diffuse"), 1.0f, 0.0f, 0.0f);
    glUniform3f(sphereShader.getUniform("material.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(sphereShader.getUniform("material.shininess"), objectShininess);

    glUniform3fv(sphereShader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(sphereShader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(sphereShader.getUniform("light.specular"), 1, &lightSpecular[0]);
    glDrawElements(GL_TRIANGLES, sphereObject.indices.size(), GL_UNSIGNED_INT, 0);




    //skybox
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