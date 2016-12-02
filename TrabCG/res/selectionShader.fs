#version 330
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

in mat4 transform;
in mat4 model;

uniform Material material;
uniform Light light;

out vec4 color;

float ambientCoefficient = 0.05;

void main()
{
	vec3 fragNormal = normalize(light.position - fragPos);

	vec3 normal = vec3(1, 0, 0);
	vec3 surfacePos = vec3(1, 0, 0);
	vec4 surfaceColor = vec4(1, 0, 0, 1);
	vec3 surfaceToLight = vec3(1, 0, 1);
	
	//Ambient
	vec3 ambient = ambientCoefficient * surfaceColor.rgb * 1;

	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
	vec3 diffuse = vec3(1, 0, 0);
	
	color = vec4(1.0, 0.0, 0.0, 1.0);
}