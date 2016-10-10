#version 330 core

layout (location = 0) in vec3 position;

out vec3 textureDir;

uniform mat4 view;
uniform mat4 projection;


void main()
{
	//正规矩阵被定义为“模型矩阵左上角的逆矩阵的转置矩阵”
	vec4 tempPosition = projection * view * vec4(position, 1.0f);
	//gl_Position = tempPosition;
	gl_Position = vec4(tempPosition.x, tempPosition.y, tempPosition.w, tempPosition.w);
	textureDir = position;
}
