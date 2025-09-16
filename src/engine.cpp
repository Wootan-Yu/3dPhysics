#include "engine.h"

Engine::Engine()
{
	init();
}

Engine::~Engine()
{
    //VAO
    glDeleteVertexArrays(1, &VAOplane);
    glDeleteVertexArrays(1, &VAOPhysicsCube);
	glDeleteVertexArrays(1, &VAOOutline);
	glDeleteVertexArrays(1, &VAOsphere);
	glDeleteVertexArrays(1, &VAOskybox);

	//VBO, EBO
	//plane
    glDeleteBuffers(1, &VBOplane);
	glDeleteBuffers(1, &planeEBO);
	//cube physics
    glDeleteBuffers(1, &VBOPhysicsCube);
	glDeleteBuffers(1, &VBOOutline);
    //sphere
    glDeleteBuffers(1, &VBOsphere);
	glDeleteBuffers(1, &EBOsphere);
	glDeleteBuffers(1, &sphereInstanceVBO);
    //skybox
    glDeleteBuffers(1, &VBOskybox);


    //textures
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
    glDeleteTextures(1, &depthMap);

    //framebuffer
	glDeleteFramebuffers(1, &depthMapFBO);
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
    //plane
    /*
    float planeVertices[] = {
		 // positions          // texture    // normals
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top left 
    };
    */

    /*
	float planeVertices[] = {
		// positions            // texture      // normals
		 25.0f,  0.0f,  25.0f,  25.0f,  0.0f,   0.0f, 1.0f, 0.0f, // top right
		 25.0f,  0.0f, -25.0f,  25.0f, 25.0f,   0.0f, 1.0f, 0.0f, // bottom right
		-25.0f,  0.0f, -25.0f,   0.0f, 25.0f,   0.0f, 1.0f, 0.0f, // bottom left
		-25.0f,  0.0f,  25.0f,   0.0f,  0.0f,   0.0f, 1.0f, 0.0f, // top left 
	};
    unsigned int planeIndices[] = {
        0, 3, 1,   // first triangle
        1, 3, 2    // second triangle
    };
    
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
    */

    float planeVertices[] = {
        // positions            // texcoords    //normals               
        -25.0f, -0.5f,  25.0f,  0.0f,  0.0f,    0.0f, 1.0f, 0.0f,  // bottom-left
         25.0f, -0.5f,  25.0f,  25.0f, 0.0f,    0.0f, 1.0f, 0.0f,  // bottom-right
        -25.0f, -0.5f, -25.0f,  0.0f,  25.0f,   0.0f, 1.0f, 0.0f,  // top-left

        -25.0f, -0.5f, -25.0f,  0.0f,  25.0f,   0.0f, 1.0f, 0.0f,  // top-left
         25.0f, -0.5f,  25.0f,  25.0f, 0.0f,    0.0f, 1.0f, 0.0f,  // bottom-right
         25.0f, -0.5f, -25.0f,  25.0f, 25.0f,   0.0f, 1.0f, 0.0f   // top-right
    };

    // plane VAO
    unsigned int planeVBO;
    glGenVertexArrays(1, &VAOplane);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(VAOplane);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glBindVertexArray(0);




	//physics cube
    float physicsCubeVertices[] = {
		//positions           // texture    // normals
        // Back face (0, 0, -1)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,

        // Front face (0, 0, 1)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,

        // Left face (-1, 0, 0)
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,

        // Right face (1, 0, 0)
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,

         // Bottom face (0, -1, 0)
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,

         // Top face (0, 1, 0)
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f
    };


   

    glGenVertexArrays(1, &VAOPhysicsCube);
    glGenBuffers(1, &VBOPhysicsCube);
    
    glBindVertexArray(VAOPhysicsCube);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOPhysicsCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(physicsCubeVertices), physicsCubeVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);



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

    glGenVertexArrays(1, &VAOOutline);
    glGenBuffers(1, &VBOOutline);

    glBindVertexArray(VAOOutline);
    glBindBuffer(GL_ARRAY_BUFFER, VBOOutline);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeEdges), cubeEdges, GL_STATIC_DRAW);

    // position only
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);



	//quad for visualizing depth map
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }



    //sphere
    sphereObject = generateSphere(1.f, 64, 32); // radius = 1.0, resolution

    glGenVertexArrays(1, &VAOsphere);
    glGenBuffers(1, &VBOsphere);
    glGenBuffers(1, &EBOsphere);
    glGenBuffers(1, &sphereInstanceVBO); // <--- instancing buffer created here

    glBindVertexArray(VAOsphere);

    // Vertex data (positions + normals)
    glBindBuffer(GL_ARRAY_BUFFER, VBOsphere);
    glBufferData(GL_ARRAY_BUFFER, sphereObject.vertices.size() * sizeof(float), sphereObject.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOsphere);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereObject.indices.size() * sizeof(unsigned int), sphereObject.indices.data(), GL_STATIC_DRAW);

    // Vertex attributes: position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    // Vertex attributes: normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Instancing matrix attribute
    glBindBuffer(GL_ARRAY_BUFFER, sphereInstanceVBO);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

    std::size_t vec4Size = sizeof(glm::vec4);
    for (GLuint i = 0; i < 4; i++) {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
        glVertexAttribDivisor(2 + i, 1);
    }

    glBindVertexArray(0); // all done

    



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

    
    sphere_bodies.reserve(amount);
    sphereModels.resize(amount);

    //sphere
    JPH::SphereShapeSettings sphereSettings(1.0);
    JPH::ShapeRefC sphereShape = sphereSettings.Create().Get();

    for (uint16_t i = 0; i < amount; i++)
    {
        JPH::BodyCreationSettings ballSettings(
            sphereShape,
            generateRandomPosition(),
            JPH::Quat::sIdentity(),
            JPH::EMotionType::Dynamic,           // movable body
            Layers::MOVING                       // your object layer
        );

        ballSettings.mMassPropertiesOverride.mMass = 5.f; // lighter = falls slower (but still gravity applies)
        ballSettings.mLinearDamping = 0.9f; // slows velocity each tick
        ballSettings.mRestitution = 0.8f;

        JPH::BodyID sphereBodyID = bodyInterface->CreateAndAddBody(ballSettings, JPH::EActivation::Activate);
        sphere_bodies.push_back(sphereBodyID);
    }
    



    //cube
    JPH::BoxShapeSettings boxSettings(JPH::Vec3(0.5f, 0.5f, 0.5f)); // 1x1x1 cube
    JPH::ShapeRefC cubeShape = boxSettings.Create().Get();

    JPH::BodyCreationSettings cubeSettings(
        cubeShape,
        JPH::RVec3(0.0f, 30.0f, 0.0f),        // <-- initial position (y = 5 units above ground)
        JPH::Quat::sIdentity(),              // no rotation
        JPH::EMotionType::Dynamic,           // movable body
        Layers::MOVING                       // your object layer
    );

    cubeSettings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
    cubeSettings.mMassPropertiesOverride.mMass = 15.f; // lighter = falls slower (but still gravity applies)
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
	debugDepthQuad.loadShaderProgramFromFile(RESOURCES_PATH "debugQuadVert.vert", RESOURCES_PATH "debugQuadFrag.frag"); //debug quad shader for visualizing depth map
    depthShader.loadShaderProgramFromFile(RESOURCES_PATH "depthShaderVert.vert", RESOURCES_PATH "depthShaderFrag.frag"); //shadow mapping depth shader

    planeShader.loadShaderProgramFromFile(RESOURCES_PATH "planeVert.vert", RESOURCES_PATH "planeFrag.frag"); //plane

    //cube
    physicsCubeShader.loadShaderProgramFromFile(RESOURCES_PATH "physicsCubeVert.vert", RESOURCES_PATH "physicsCubeFrag.frag"); 
    outlineShader.loadShaderProgramFromFile(RESOURCES_PATH "outlineVert.vert", RESOURCES_PATH "outlineFrag.frag");

    sphereShader.loadShaderProgramFromFile(RESOURCES_PATH "sphereVert.vert", RESOURCES_PATH "sphereFrag.frag"); //sphere
    skyboxShader.loadShaderProgramFromFile(RESOURCES_PATH "skybox/vertShader.vert", RESOURCES_PATH "skybox/fragShader.frag"); //skybox
}

void Engine::initTexture()
{
    //plane texture
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

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
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

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

void Engine::initShadows()
{
    //shadow mapping framebuffer
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	debugDepthQuad.bind();
    glUniform1i(debugDepthQuad.getUniform("depthMap"), 0);

	/*physicsCubeShader.bind();
    glUniform1i(physicsCubeShader.getUniform("diffuseTexture"), 0);
    glUniform1i(physicsCubeShader.getUniform("shadowMap"), 0);*/
}

void Engine::run()
{
    initShape();
    initPhysics();
    initShader();
    initTexture();
	initShadows();
	processInput(); //mouse, cursor and scroll input
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        keyInput(); //key input
		update(deltaTime);
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
            JPH::RVec3(0.0f, 30.0f, 0.0f),
            JPH::Quat::sIdentity(),
            JPH::EActivation::Activate
        );

        bodyInterface->SetLinearAndAngularVelocity(
            cubeBodyID,
            JPH::Vec3(0, 0, 0),  // linear velocity
            JPH::Vec3(0, 0, 0)   // angular velocity
        );
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        for (uint16_t i = 0; i < amount; i++)
        {
            bodyInterface->SetPositionAndRotation(
                sphere_bodies[i],
                generateRandomPosition(),
                JPH::Quat::sIdentity(),
                JPH::EActivation::Activate
            );

            bodyInterface->SetLinearAndAngularVelocity(
                sphere_bodies[i],
                JPH::Vec3(0, 0, 0),
                JPH::Vec3(0, 0, 0)
            );
        }
    }


    //std::cout << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << '\n';
}

void Engine::update(float frameDeltaTime)
{
    // Create temporary memory allocator and job system
    static JPH::TempAllocatorImpl tempAllocator(10 * 1024 * 1024);
    static JPH::JobSystemThreadPool jobSystem(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);

    static const float fixedDeltaTime = 1.0f / 120.0f;
    static float accumulator = 0.0f;

    // Clamp large delta times to prevent spiral of death
    frameDeltaTime = std::min(frameDeltaTime, 0.1f);
    accumulator += frameDeltaTime;

    while (accumulator >= fixedDeltaTime)
    {
        // Substep physics
        physicsSystem.Update(fixedDeltaTime, 1, &tempAllocator, &jobSystem);
        accumulator -= fixedDeltaTime;
    }

    //just uncomment this out if i want the cube to move
    // Fetch cube transform
    //JPH::RMat44 cube = bodyInterface->GetCenterOfMassTransform(cubeBodyID);
    //cube.StoreFloat4x4((JPH::Float4*)cubeMat);  // reinterpret as float[16]
    //cubeModel = glm::make_mat4(cubeMat);


    for (uint16_t i = 0; i < amount; i++)
    {
        JPH::RMat44 sphere = bodyInterface->GetCenterOfMassTransform(sphere_bodies[i]);
        sphere.StoreFloat4x4((JPH::Float4*)sphereMat);
        sphereModels[i] = glm::make_mat4(sphereMat);
    }

    glBindBuffer(GL_ARRAY_BUFFER, sphereInstanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sphereModels.size() * sizeof(glm::mat4), sphereModels.data());
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

    //plane
    planeShader.bind();
    glUniformMatrix4fv(planeShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(planeShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(planeShader.getUniform("texture1"), 0); // set the texture unit 1 to texture2

	glBindVertexArray(VAOplane);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));
	
    glUniformMatrix4fv(planeShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(planeShader.getUniform("light.position"), 1, &lightPos[0]);
    glUniform3fv(planeShader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform3fv(planeShader.getUniform("material.ambient"), 1, &materialAmbient[0]);
    glUniform3fv(planeShader.getUniform("material.diffuse"), 1, &materialDiffuse[0]);
    glUniform3fv(planeShader.getUniform("material.specular"), 1, &materialSpecular[0]);
    glUniform1f(planeShader.getUniform("material.shininess"), objectShininess);

    glUniform3fv(planeShader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(planeShader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(planeShader.getUniform("light.specular"), 1, &lightSpecular[0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    

    
    //outline
    outlineShader.bind();
    glUniformMatrix4fv(outlineShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(outlineShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);

    static glm::vec3 lineColor(1.f, 1.f, 1.f);

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

    glUniform3fv(sphereShader.getUniform("light.position"), 1, &lightPos[0]);
    glUniform3fv(sphereShader.getUniform("viewPosition"), 1, &cameraPos[0]);

    glUniform3f(sphereShader.getUniform("material.ambient"), 0.2f, 0.f, 0.f);
    glUniform3f(sphereShader.getUniform("material.diffuse"), 1.0f, 0.0f, 0.0f);
    glUniform3f(sphereShader.getUniform("material.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(sphereShader.getUniform("material.shininess"), objectShininess);

    glUniform3fv(sphereShader.getUniform("light.ambient"), 1, &lightAmbient[0]);
    glUniform3fv(sphereShader.getUniform("light.diffuse"), 1, &lightDiffuse[0]);
    glUniform3fv(sphereShader.getUniform("light.specular"), 1, &lightSpecular[0]);

    glBindVertexArray(VAOsphere);
    glDrawElementsInstanced(GL_TRIANGLES, sphereObject.indices.size(), GL_UNSIGNED_INT, 0, amount);




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

void Engine::drawbox(Shader& shader)
{
    shader.bind();
    //plane
    glBindVertexArray(VAOplane);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);  // Make sure this is the correct texture ID

    cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 0.35f, 0.0));
    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &cubeModel[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 6);




    //cube
    glBindVertexArray(VAOPhysicsCube);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);  // Make sure this is the correct texture ID

	//just comment this out if i want the cube to move
	cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, glm::vec3(0.8f, 1.5f, 0.3));
    cubeModel = glm::scale(cubeModel, glm::vec3(0.5f));

    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &cubeModel[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //just comment this out if i want the cube to move
    cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, glm::vec3(2.0f, 0.1f, 1.0));
    cubeModel = glm::scale(cubeModel, glm::vec3(0.5f));

    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &cubeModel[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //just comment this out if i want the cube to move
    cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, glm::vec3(-1.0f, 0.1f, 2.0));
    cubeModel = glm::rotate(cubeModel, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    cubeModel = glm::scale(cubeModel, glm::vec3(0.25f));

    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &cubeModel[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Engine::drawQuad()
{
    //quad for visualizing depth map
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Engine::render() 
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // 1. first render to depth map 
    float near_plane = 1.0f, far_plane = 7.5f; 
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane); 
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0)); 
    lightSpaceMatrix = lightProjection * lightView; 
    
    depthShader.bind(); 
    glUniformMatrix4fv(depthShader.getUniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix)); 
    
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT); 
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO); 
    glClear(GL_DEPTH_BUFFER_BIT); 
    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, texture2); 
    drawbox(depthShader);


    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    
    //reset viewport 
    int width = 0, height = 0; 
    glfwGetFramebufferSize(window, &width, &height); 
    glViewport(0, 0, width, height); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    
    // 2. then render scene as normal with shadow mapping (using depth map) 
    physicsCubeShader.bind(); 
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 
    projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 45.0f); 
    
    glUniformMatrix4fv(physicsCubeShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]); 
    glUniformMatrix4fv(physicsCubeShader.getUniform("view"), 1, GL_FALSE, &view[0][0]); 
    glUniform3fv(physicsCubeShader.getUniform("viewPos"), 1, &cameraPos[0]); 
    glUniform3fv(physicsCubeShader.getUniform("lightPos"), 1, &lightPos[0]); 
    glUniformMatrix4fv(physicsCubeShader.getUniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix)); 
    
    // Bind color texture (texture2) to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(physicsCubeShader.getUniform("diffuseTexture"), 0);

    // Bind depth map to texture unit 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glUniform1i(physicsCubeShader.getUniform("shadowMap"), 1);
    drawbox(physicsCubeShader); 
    
    
    debugDepthQuad.bind();
    glUniform1f(debugDepthQuad.getUniform("nearPlane"), near_plane);
    glUniform1f(debugDepthQuad.getUniform("farPlane"), far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    
    //drawQuad();


    
    //drawShape();


    glfwSwapBuffers(window); 
    glfwPollEvents(); 
}
