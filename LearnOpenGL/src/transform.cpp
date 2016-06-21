#include "transform.h"
#include <SOIL\SOIL.h>

Transform::Transform()
{
	mat4 trans;
	rotate(trans, 90.0f, vec3(0.0f, 0.0f, 1.0f));
	scale(trans, vec3(0.5f, 0.5f, 0.5f));

	shader = new ShaderHandle("transform");

	this->initVAO();

	this->initTexture();

	this->initMatrix();
}

void Transform::initVAO()
{
	GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

	GLuint VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Transform::initTexture()
{
	glGenTextures(1, &this->texture1);
	glGenTextures(1, &this->texture2);
	//绑定第一个纹理
	glBindTexture(GL_TEXTURE_2D, this->texture1);
	//设置过滤器
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//设置环绕方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//加载纹理
	int width;
	int height;
	unsigned char* image = SOIL_load_image("../resource/crate.jpg", &width, & height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	//释放数据
	SOIL_free_image_data(image);

	//绑定第二个纹理
	glBindTexture(GL_TEXTURE_2D, this->texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	image = SOIL_load_image("../resource/child.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Transform::initMatrix()
{
	this->trans = rotate(this->trans, radians(90.0f), vec3(0.0f, 0.0f, 1.0f));
//	this->trans = scale(this->trans, vec3(0.5f, 0.5f, 0.5f));
}

void Transform::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture1);
	glUniform1i(glGetUniformLocation(this->shader->getProgram(), "ourTexture1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->texture2);
	glUniform1i(glGetUniformLocation(this->shader->getProgram(), "ourTexture2"), 1);


	this->trans = translate(mat4(1.0f), vec3(sin(glfwGetTime()), 0.0f, 0.0f));
	this->trans = rotate(this->trans, radians(10.0f * (GLfloat)glfwGetTime()), vec3(0.0f, 0.0f, 1.0f));
	//注：scale 值取到负值时会被反转 所以效果很诡异
	this->trans = scale(this->trans, vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));

	GLuint transformLoc = glGetUniformLocation(shader->getProgram(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}