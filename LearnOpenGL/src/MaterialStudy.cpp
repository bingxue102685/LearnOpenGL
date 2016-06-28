#include "MaterialStudy.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

MaterialStudy::MaterialStudy()
{
	//加载纹理光照数据，数据来自,http://devernay.free.fr/cours/opengl/materials.html
	this->initMaterialConfig();
	this->initVAO();
	this->cubeShader = new ShaderHandle("materialcube");
	this->lightShader = new ShaderHandle("materiallight");
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_LINE_SMOOTH);
	srand(time(0));
	currentMatrialIndex = floor(rand() % 24);
}

void MaterialStudy::initMaterialConfig()
{
	//读取material.config文件的中的数据，从网页中摘取
	string cotentName[4] = {
		"Ambient",
		"Diffuse",
		"Specular",
		"Shininess"
	};

	

	char buffer[256];
	memset(buffer, 0, 256);

	char* p;
	string name;
	vec3 tempvalue;
	int valuecount = 0;
	const char* split= "\t";
	int contentIndex = 0;
	int marterialIndex = 0;
	
	ifstream myfile;

	myfile.open("../resource/material.config");
 	while(!myfile.eof()) {
		myfile.getline(buffer, 256);
		p = strtok(buffer, split);

		hash_map<string, vec3> contentValue;
		name = string(p);
		tempvalue = vec3(0.0f);
		while(p != NULL) {
			p = strtok(NULL, split);
			tempvalue[valuecount] = atof(p);
			valuecount++;
			if (contentIndex == 3 && valuecount == 1) {
				contentValue.insert(pair<string, vec3>(cotentName[contentIndex], tempvalue * 128.0f));
				contentIndex = 0;
				valuecount = 0;
				break;
			}
			if (valuecount == 3) {
				contentValue.insert(pair<string, vec3>(cotentName[contentIndex], tempvalue));

				contentIndex ++;
				valuecount = 0;
				tempvalue = vec3(0.0f);
			}
		}
		this->materials.insert(pair<string, hash_map<string, vec3>>(name, contentValue));
		this->materialNames[marterialIndex] = name;
		marterialIndex ++;
	}
}

void MaterialStudy::initVAO()
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	GLuint VBO;

	glGenVertexArrays(1, &this->cubeVAO);
	glGenVertexArrays(1, &this->lightVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glBindVertexArray(this->lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
//此render为渲染devernay.free.fr
void MaterialStudy::render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double currentTime = glfwGetTime();
	vec3 lightPos(1.8f * sin(currentTime), -0.5f, 1.8f * cos(currentTime));
	vec3 lightColor(1.0f, 1.0f, 1.0f);

	mat4 model;
	mat4 view;
	mat4 projection;

	cubeShader->UseProgram();
	model = rotate(model, radians(30.0f), vec3(0.0f, 1.0f ,0.0f));
	view = lookAt(vec3(0.0f, -1.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "lightcolor"), 1, value_ptr(lightColor));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "lightPos"), 1, value_ptr(lightPos));
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "viewPos"), 0.0f, 2.0f, 5.0f);
	/*
		可用的材质
		emerald, jade, obsidian, pearl, ruby, turquoise, brass, bronze, chrome, copper , gold, silver
		black plastic, cyan plastic, green plastic, red plastic, white plastic, yellow plastic, black rubber
        cyan rubber, green rubber, red rubber, white rubber, yellow rubber
	*/
	auto currentMaterial = materials[materialNames[currentMatrialIndex]];
	//auto currentMaterial = materials["emerald"];
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "material.ambient"), 1, value_ptr(currentMaterial["Ambient"]));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "material.diffuse"), 1, value_ptr(currentMaterial["Diffuse"]));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "material.specular"),1, value_ptr(currentMaterial["Specular"]));
	glUniform1f(glGetUniformLocation(cubeShader->getProgram(), "material.shininess"),currentMaterial["Shininess"].x);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.ambient"),1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);

	glBindVertexArray(this->cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	model = translate(mat4(1.0f), lightPos);
	model = rotate(model, radians(-30.0f), vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(0.5f, 0.5f, 0.5f));

	lightShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glBindVertexArray(this->lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

void MaterialStudy::render2()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double currentTime = glfwGetTime();
	vec3 lightPos(1.5f, -0.5f, 1.0f);
	vec3 lightColor;
	//与教程有点出入，在此，我改变光源的颜色。
	//包证颜色在 0  - 1之间
	lightColor.x = sin(currentTime * 0.2f) / 2 + 0.5;
	lightColor.y = sin(currentTime * 0.7f) / 2 + 0.5;
	lightColor.z = sin(currentTime * 1.3f) / 2 + 0.5;

	mat4 model;
	mat4 view;
	mat4 projection;

	cubeShader->UseProgram();
	model = rotate(model, radians(30.0f), vec3(0.0f, 1.0f ,0.0f));
	view = lookAt(vec3(0.0f, 2.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "lightcolor"), lightColor.x, lightColor.y, lightColor.z);
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "lightPos"), 1, value_ptr(lightPos));
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "viewPos"), 0.0f, 2.0f, 5.0f);
	/*glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(cubeShader->getProgram(), "material.shininess"), 32.0f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.ambient"),0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);*/

	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(cubeShader->getProgram(), "material.shininess"), 32.0f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.ambient"),0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(cubeShader->getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);

	glBindVertexArray(this->cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	model = translate(mat4(1.0f), lightPos);
	model = rotate(model, radians(-30.0f), vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(0.5f, 0.5f, 0.5f));

	lightShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glBindVertexArray(this->lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}