#version 330 core

in vec3 textureDir;
out vec4 color;
uniform samplerCube cubemap;

void main()
{
	color = texture(cubemap, textureDir);
}
