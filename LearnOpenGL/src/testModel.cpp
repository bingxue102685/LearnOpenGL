#include "testModel.h"


TestModel::TestModel()
{
	this->shader = new ShaderHandle("modelstudy");

	this->model = new Model("../resource/model/sakura/SAKURA.obj");

	glEnable(GL_DEPTH_TEST);
}

void TestModel::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double currentTime = glfwGetTime();

	shader->UseProgram();

	vec3 lightPos(0.0f, 0.0f, 5.0f);
	vec3 viewPosition(0.0f, 0.0f, 5.0f);

	mat4 model(0.0);
	mat4 view(1.0);
	mat4 projection(1.0);

	view = lookAt(viewPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));

	this->model->Draw(this->shader);
}

