#include "AdvancedGLSLStudy.h"


AdvancedGLSLStudy::AdvancedGLSLStudy()
{
	pointShader = new ShaderHandle("advancedglslpoint");
	fragCoordShader = new ShaderHandle("advancedglslfragcoord");
	glEnable(GL_PROGRAM_POINT_SIZE);
	initUBO();
	initVAO();
}

void AdvancedGLSLStudy::initVAO()
{

	GLfloat skyboxVertices[] = {
        // Positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
   
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->pointVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),  NULL, GL_STATIC_DRAW);
	
	glBindVertexArray(this->pointVAO);
	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(bufferPtr, &skyboxVertices, sizeof(skyboxVertices));
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	
	glBindVertexArray(0);
}

void AdvancedGLSLStudy::initUBO()
{
	redShader = new ShaderHandle("advancedglslred");
	greenShader = new ShaderHandle("advancedglslgreen");
	blueShader = new ShaderHandle("advancedglslblue");
	yellowShader = new ShaderHandle("advancedglslyellow");

	//得到shader中uniform block索引
	GLuint redMatricesIndex = glGetUniformBlockIndex(redShader->getProgram(), "Matrices");
	GLuint greenMatricesIndex = glGetUniformBlockIndex(greenShader->getProgram(), "Matrices");
	GLuint blueMatricesIndex = glGetUniformBlockIndex(blueShader->getProgram(), "Matrices");
	GLuint yellowMatricesIndex = glGetUniformBlockIndex(yellowShader->getProgram(), "Matrices");

	//把uniform block索引绑定到绑定点上
	glUniformBlockBinding(redShader->getProgram(), redMatricesIndex, 0);
	glUniformBlockBinding(greenShader->getProgram(), greenMatricesIndex, 0);
	glUniformBlockBinding(blueShader->getProgram(), blueMatricesIndex, 0);
	glUniformBlockBinding(yellowShader->getProgram(), yellowMatricesIndex, 0);

	//初始化ubo,
	GLuint UBO;
	glGenBuffers(1, &UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//绑定ubo到绑定点上
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);

	//view
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	mat4 view = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//projection
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	mat4 projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void AdvancedGLSLStudy::render()
{
	//renderPoint();
	//renderFrogCoord();
	renderUBO();
}


void AdvancedGLSLStudy::renderUBO()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mat4 model(1.0f);

	//左上角
	redShader->UseProgram();
	model = translate(mat4(1.0f), vec3(-2.0f, 2.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(redShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(this->pointVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//右上角
	greenShader->UseProgram();
	model = translate(mat4(1.0f), vec3(2.0f, 2.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(greenShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(this->pointVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//左下角
	blueShader->UseProgram();
	model = translate(mat4(1.0f), vec3(-2.0f, -2.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(blueShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(this->pointVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//右下角
	yellowShader->UseProgram();
	model = translate(mat4(1.0f), vec3(2.0f, -2.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(yellowShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(this->pointVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void AdvancedGLSLStudy::renderPoint()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mat4 model(1.0f);
	mat4 view;
	mat4 projection;

	view = lookAt(vec3(0.0f, 0.0f, 4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	pointShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(pointShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(pointShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(pointShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glBindVertexArray(this->pointVAO);
	glDrawArrays(GL_POINTS, 0, 36);
	glBindVertexArray(0);
}

void AdvancedGLSLStudy::renderFrogCoord()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mat4 model(1.0f);
	mat4 view;
	mat4 projection;

	view = lookAt(vec3(0.0f, 0.0f, 4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	fragCoordShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(fragCoordShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(fragCoordShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(fragCoordShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glBindVertexArray(this->pointVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}