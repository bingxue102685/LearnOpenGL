#include "LightingMapStudy.h"
#include <SOIL\SOIL.h>


LightingMapStudy::LightingMapStudy()
{
	this->lightShader = new ShaderHandle("lightmaplight");
	this->cubeShader = new ShaderHandle("lightmapcube");
	this->initTexture();
	this->initVAO();
	glEnable(GL_DEPTH_TEST);
}

void LightingMapStudy::initVAO()
{
	GLfloat vertices[] = {
		// Positions           // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	GLuint VBO;
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->lightVAO);
	glGenVertexArrays(1, &this->cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindVertexArray(this->cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glBindVertexArray(this->lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void LightingMapStudy::initTexture()
{
	glGenTextures(1, &this->cubeDiffuseTexture);
	glGenTextures(1, &this->cubeSpecularTexture);

	glBindTexture(GL_TEXTURE_2D, this->cubeDiffuseTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	int width;
	int height;
	unsigned char* image = SOIL_load_image("../resource/container2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, this->cubeSpecularTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	image = SOIL_load_image("../resource/container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, this->cubeEmissionTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	image = SOIL_load_image("../resource/matrix.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


}

void LightingMapStudy::render()
{
	//注：次渲染与教程有出入，没有设置光照限制，所以运行的效果偏亮，如果想加上也可以
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat currentTime = glfwGetTime();

	//cube
	this->cubeShader->UseProgram();

	mat4 model(1.0f);
	mat4 view(1.0f);
	mat4 projection(1.0f);
	GLuint modelLocation;
	GLuint viewLocation;
	GLuint projectLocation;
	vec3 viewPos(0.0f, -1.0f, 5.0f);
	vec3 lightColor(1.0f, 1.0f, 1.0f);
	vec3 lightPostion(2 * sin(currentTime), 0.0f, 2 * cos(currentTime));

	model = rotate(model,-20.0f * radians(currentTime), vec3(0.0f, 1.0f, 0.0f));
	view = lookAt(viewPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	
	modelLocation = glGetUniformLocation(cubeShader->getProgram(), "model");
	viewLocation = glGetUniformLocation(cubeShader->getProgram(), "view");
	projectLocation = glGetUniformLocation(cubeShader->getProgram(), "projection");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE,value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE,value_ptr(view));
	glUniformMatrix4fv(projectLocation, 1, GL_FALSE,value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->cubeDiffuseTexture);
	glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "material.diffuse"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->cubeSpecularTexture);
	glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "material.specular"), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->cubeEmissionTexture);
	glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "material.emission"), 2);
	glUniform1f(glGetUniformLocation(cubeShader->getProgram(), "material.shininess"),0.6f * 128.0f);
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "lightcolor"), 1, value_ptr(lightColor));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "lightPos"), 1, value_ptr(lightPostion));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "viewPos"), 1,value_ptr(viewPos));

	glBindVertexArray(this->cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//light
	this->lightShader->UseProgram();
	model = translate(mat4(1.0f), lightPostion);
	model = rotate(model, radians(-30.0f), vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(0.5f, 0.5f, 0.5f));

	modelLocation = glGetUniformLocation(lightShader->getProgram(), "model");
	viewLocation = glGetUniformLocation(lightShader->getProgram(), "view");
	projectLocation = glGetUniformLocation(lightShader->getProgram(), "projection");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE,value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE,value_ptr(view));
	glUniformMatrix4fv(projectLocation, 1, GL_FALSE,value_ptr(projection));

	glBindVertexArray(this->lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);	
}
