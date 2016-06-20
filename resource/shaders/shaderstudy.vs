#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
uniform float transform;
out vec3 ourColor;
void main()
{
	gl_Position = vec4(transform + position.x, position.y, position.z, 1.0f);
	ourColor = color;
}