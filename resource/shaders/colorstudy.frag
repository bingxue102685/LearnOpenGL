#version 330 core

uniform vec3 objectcolor;
uniform vec3 lightcolor;

out vec4 color;

void main()
{
	color = vec4(objectcolor * lightcolor, 1.0f);
}
