#version 330 core
out vec4 FragColor;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

//uniform sampler2D texture_diffuse1;

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // Normalize to [0,1]
    FragColor = vec4(depth, 0.0, 0.0, 1.0); // Grayscale depth
}
