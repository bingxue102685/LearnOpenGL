#version 330 core
in vec2 TexCoord;
out vec4 color;
uniform sampler2D ourTexture1;

void main()
{
	color = texture2D(ourTexture1, TexCoord);
}