#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoords;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); //输出所有顶点的位置，包括未定义的（插值）
	TexCoords = texCoords;
}