#include "ColorStudy.h"

ColorStudy::ColorStudy()
{
	this->colorShader = new ShaderHandle("colorstudy");
	this->lightShader = new ShaderHandle("light");
	this->initVAO();
}

ColorStudy::~ColorStudy()
{
}

void ColorStudy::initVAO()
{
	GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	GLuint VBO;
	glGenVertexArrays(1, &this->ColorVAO);
	glGenVertexArrays(1, &this->LightVAO);
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->ColorVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(this->LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void ColorStudy::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 model(1.0f);
	model = rotate(model, radians(30.0f), vec3(0.0f, 1.0f ,0.0f));
	mat4 view = lookAt(vec3(0.0f, 2.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	mat4 projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	colorShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(colorShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(colorShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(colorShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform3f(glGetUniformLocation(colorShader->getProgram(), "objectcolor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(colorShader->getProgram(), "lightcolor"), 1.0f, 1.0f, 1.0f);
	glBindVertexArray(this->ColorVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	model = translate(mat4(1.0f), vec3(1.2f, 1.0f, 2.0f));
	model = rotate(model, radians(-30.0f), vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(0.5f, 0.5f, 0.5f));

	lightShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(colorShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(colorShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(colorShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glBindVertexArray(this->LightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}