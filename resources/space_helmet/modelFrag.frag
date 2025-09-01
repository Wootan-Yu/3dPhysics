#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_emissive1;
uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{
    //FragColor = mix(texture(texture_diffuse1, TexCoords), texture(texture_emissive1, TexCoords), 0.2); //this for 2 textures



    // Surface normal
    vec3 N = normalize(Normal);

    // View direction
    vec3 I = normalize(Position - cameraPos);

    // Reflection vector
    vec3 R = reflect(I, N);

    // Sample cubemap
    vec3 reflectedColor = texture(skybox, R).rgb;

    // Base texture color
    vec3 baseColor = mix(
        texture(texture_diffuse1, TexCoords).rgb,
        texture(texture_emissive1, TexCoords).rgb,
        0.2
    );

    // Combine base with reflection
    float reflectStrength = 0.4; // adjust how reflective the object is
    vec3 finalColor = mix(baseColor, reflectedColor, reflectStrength);

    FragColor = vec4(finalColor, 1.0);
}