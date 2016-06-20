#include "shaderStudy.h"
#include <assert.h>
#include <fstream>

ShaderStudy::ShaderStudy()
{
	shader = new ShaderHandle("shaderstudy");

	this->initVAO();
}

void ShaderStudy::initVAO()
{
	GLfloat vertices[] = {
	// 位置                 // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}



void ShaderStudy::render()
{
	this->transform = glGetUniformLocation(this->shaderProgram, "transform");
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->UseProgram();
	glBindVertexArray(this->VAO);

	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = sin(timeValue) / 2;
	glUniform1f(this->transform, greenValue);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}