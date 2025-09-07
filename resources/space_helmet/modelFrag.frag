#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position; // fragment world-space position

// Textures
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_emissive1;
uniform samplerCube skybox;

// Camera
uniform vec3 viewPosition;

// Lighting
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
    // Base texture blend
    vec3 baseColor = mix(
        texture(texture_diffuse1, TexCoords).rgb,
        texture(texture_emissive1, TexCoords).rgb,
        0.4
    );

    // Normalized vectors
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPosition - Position);
    vec3 lightDir = normalize(light.position - Position);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Ambient
    vec3 ambient = material.ambient * light.ambient;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    // Specular (Blinn-Phong)
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.specular;

    // Reflection from skybox
    vec3 I = normalize(Position - viewPosition); // view ray
    vec3 R = reflect(I, norm);                // reflected ray
    vec3 reflectedColor = texture(skybox, R).rgb;

    float reflectStrength = 0.2; // adjust reflection intensity

    // Lighting result
    vec3 lightingResult = ambient + diffuse + specular;

    // Combine lighting with base color, and then with reflection
    vec3 litColor = lightingResult * baseColor;
    vec3 finalColor = mix(litColor, reflectedColor, reflectStrength);

    FragColor = vec4(finalColor, 1.0);
}
