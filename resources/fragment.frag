#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; // fragment position in world space

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool choice; // 0 = texture1, 1 = texture2

uniform vec3 lightPosition;
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
	vec4 tex;
	if (choice)
		tex = texture(texture2, TexCoord);
	else
		tex = texture(texture1, TexCoord);

	//apply Ambient lighting
    vec3 ambient = material.ambient * light.ambient;

	//apply diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	//apply specular lighting
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * light.specular;  


	vec3 result = (ambient + diffuse + specular) * tex.rgb;

    // Final color with ambient lighting
    FragColor = vec4(result, tex.a);
}