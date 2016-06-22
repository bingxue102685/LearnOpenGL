#version 330 core

uniform vec3 objectcolor;
uniform vec3 lightcolor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 fragPos;
out vec4 color;

void main()
{
	float specularStrength = 0.5f;

    vec3 lightDir = normalize(lightPos - fragPos);
	vec3 normal = normalize(Normal);

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflecDir = reflect(-lightDir, normal);
	//这个32是高光的发光值(Shininess)。一个物体的发光值越高，反射光的能力越强，散射得越少，高光点越小
	float spec = pow(max(dot(viewDir, reflecDir), 0.0), 64);

	
	
	float diff = max(dot(normal, lightDir), 0);

    float ambientStrength = 0.1f;
    vec3 ambient = (ambientStrength  + diff + spec * specularStrength) * lightcolor;
    vec3 result = ambient * objectcolor;
    color = vec4(result, 1.0f);
}
