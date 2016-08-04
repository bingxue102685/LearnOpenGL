#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	//normal传入的为局部坐标系，需要变换为世界坐标系，但不能直接乘model,需要将model转为正规矩阵
	//正规矩阵被定义为“模型矩阵左上角的逆矩阵的转置矩阵”,不甚理解，到时再说
	Normal = mat3(transpose(inverse(model))) * normal;
	Position = vec3(model * vec4(position, 1.0f));
}