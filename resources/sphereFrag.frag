#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPosition;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;


struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
    //apply Ambient lighting
    vec3 ambient = material.ambient * light.ambient;

	//apply diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	//apply specular lighting, Blinn-Phong
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
	vec3 specular = material.specular * spec * light.specular;


	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0);
}