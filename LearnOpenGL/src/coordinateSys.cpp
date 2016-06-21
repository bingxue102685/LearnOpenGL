#include "coordinateSys.h"
#include <SOIL\SOIL.h>

CoorDinateSys::CoorDinateSys()
{

	glEnable(GL_DEPTH_TEST);

	this->shader = new ShaderHandle("coordinate");

	this->initTexture();

	this->initVAO2();
}

void CoorDinateSys::initTexture()
{
	glGenTextures(1, &this->texture1);
	glGenTextures(1, &this->texture2);

	glBindTexture(GL_TEXTURE_2D, this->texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	int width = 0;
	int height = 0;
	unsigned char* image = SOIL_load_image("../resource/child.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, this->texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	image = SOIL_load_image("../resource/crate.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void CoorDinateSys::initVAO()
{

}

void CoorDinateSys::initVAO2()
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

	cubePositions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
	cubePositions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
	cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
	cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
	cubePositions[4] = glm::vec3( 2.4f, -0.4f, -3.5f);
	cubePositions[5] = glm::vec3(-1.7f,  3.0f, -7.5f);
	cubePositions[6] = glm::vec3( 1.3f, -2.0f, -2.5f);
	cubePositions[7] = glm::vec3( 1.5f,  2.0f, -2.5f);
	cubePositions[8] = glm::vec3( 1.5f,  0.2f, -1.5f);
	cubePositions[9] = glm::vec3(-1.3f,  1.0f, -1.5f);

	GLuint VBO;
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void CoorDinateSys::render2()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mat4 model(1.0f);
	model = rotate(model, radians(-45.0f), vec3(1.0f, 0.0f, 0.0f));

	mat4 view(1.0f);
	view = translate(view, vec3(0.0f, 0.0f, -3.0f));

	mat4 project(1.0f);
	project = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture1);
	glUniform1i(glGetUniformLocation(this->shader->getProgram(), "ourTexture1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->texture2);
	glUniform1i(glGetUniformLocation(this->shader->getProgram(), "ourTexture2"), 1);

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(project));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}

void CoorDinateSys::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture1);
	glUniform1i(glGetUniformLocation(this->shader->getProgram(), "ourTexture1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->texture2);
	glUniform1i(glGetUniformLocation(this->shader->getProgram(), "ourTexture2"), 1);



	GLuint modelLoc = glGetUniformLocation(shader->getProgram(), "model");
	GLuint viewLoc = glGetUniformLocation(shader->getProgram(), "view");
	GLuint projectLoc = glGetUniformLocation(shader->getProgram(), "projection");

	glBindVertexArray(this->VAO);
	for (int i = 0; i < 10; i++) {
		mat4 model(1.0f);
		mat4 view(1.0f);
		mat4 project(1.0f);
		model = translate(model, cubePositions[i]);
		model = rotate(model, radians(GLfloat(glfwGetTime())) * 5, vec3(1.0f, 0.0f, 0.0f));
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));
		project = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, value_ptr(project));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	glBindVertexArray(0);
}