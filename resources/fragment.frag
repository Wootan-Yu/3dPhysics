#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; // fragment position in world space

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool choice; // 0 = texture1, 1 = texture2

//ambient light
uniform vec3 lightColor;

//diffuse light
uniform vec3 lightPosition;

void main()
{
	vec4 tex;
	if (choice)
		tex = texture(texture2, TexCoord);
	else
		tex = texture(texture1, TexCoord);

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	//apply diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * tex.rgb;

    // Final color with ambient lighting
    FragColor = vec4(result, tex.a);
}