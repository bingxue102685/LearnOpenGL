#include "CameraStudy.h"

vec3 CameraStudy::cameraPos = vec3(0.0f, 0.0f, -1.0f);
vec3 CameraStudy::cameraFront = vec3(0.0f, 0.0f, 3.0f);
vec3 CameraStudy::cameraUp = vec3(0.0f, 1.0f, 0.0f);
bool CameraStudy::keys[1024];

CameraStudy::CameraStudy()
{
	this->initStatues();
}

void CameraStudy::initStatues()
{
	glEnable(GL_DEPTH_TEST);
	this->shader = new ShaderHandle("camera");
	this->InitVAO();
	this->InitTexture();
	
	GLFWwindow* window = RenderDelegate::getInstance()->getWindowHandle();
	glfwSetKeyCallback(window, &CameraStudy::key_callback);
	this->lastTime = 0;
	this->deltaTime = 0;
}

void CameraStudy::InitVAO()
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

	cubePositions[0] = vec3( 0.0f,  0.0f,  0.0f);
	cubePositions[1] = vec3( 2.0f,  5.0f, -15.0f);
	cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
	cubePositions[3] = vec3(-3.8f, -2.0f, -12.3f);
	cubePositions[4] = vec3( 2.4f, -0.4f, -3.5f);
	cubePositions[5] = vec3(-1.7f,  3.0f, -7.5f);
	cubePositions[6] = vec3( 1.3f, -2.0f, -2.5f);
	cubePositions[7] = vec3( 1.5f,  2.0f, -2.5f);
	cubePositions[8] = vec3( 1.5f,  0.2f, -1.5f);
	cubePositions[9] = vec3(-1.3f,  1.0f, -1.5f);

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


void CameraStudy::InitTexture()
{
	glGenTextures(1, &this->texture);
	
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width;
	int height;
	unsigned char* image = SOIL_load_image("E:\\Study\\OpenGL\\LearnOpenGL\\LearnOpenGL\\resource\\crate.jpg", &width, & height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

void CameraStudy::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	
	if(action == GLFW_PRESS)
		CameraStudy::keys[key] = true;
	else if(action == GLFW_RELEASE)
		CameraStudy::keys[key] = false;	
}

void CameraStudy::DoMovement()
{
	GLfloat cameraSpeed = 0.1f * this->deltaTime;
	if (CameraStudy::keys[GLFW_KEY_W])
	{
		CameraStudy::cameraPos += (CameraStudy::cameraFront * cameraSpeed);
	}
	
	if (CameraStudy::keys[GLFW_KEY_S])
	{
		CameraStudy::cameraPos -= (CameraStudy::cameraFront * cameraSpeed);
	}

	if (CameraStudy::keys[GLFW_KEY_A])
	{
		CameraStudy::cameraPos -= (normalize(cross(CameraStudy::cameraFront, CameraStudy::cameraUp)) * cameraSpeed);
	}

	if (CameraStudy::keys[GLFW_KEY_D])
	{
		CameraStudy::cameraPos += (normalize(cross(CameraStudy::cameraFront, CameraStudy::cameraUp)) * cameraSpeed);
	}
	
}

void CameraStudy::render()
{
	GLfloat currentFrame = glfwGetTime();
	this->deltaTime = currentFrame - this->lastTime;
	this->lastTime = currentFrame;

	this->DoMovement();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->UseProgram();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glUniform1i(glGetUniformLocation(shader->getProgram(), "ourTexture1"), 0);

	glBindVertexArray(this->VAO);

	for (int i = 0; i < 10; i++)
	{
		mat4 model;
		mat4 view;
		mat4 projection;

		model = translate(model, cubePositions[i]);
		model = rotate(model, radians((GLfloat)glfwGetTime()) * 10, vec3(1.0f, 1.0f, 1.0f));

		GLfloat radius = 10.0f;
		GLfloat camX = sin(glfwGetTime()) * radius;
		GLfloat camZ = cos(glfwGetTime()) * radius;
		//                  摄像机的位置，          摄像机指向的位置  ，     摄像机上方向
		//view = lookAt(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); 
		view = lookAt(CameraStudy::cameraPos, CameraStudy::cameraPos + CameraStudy::cameraFront, CameraStudy::cameraUp);

		projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);

}