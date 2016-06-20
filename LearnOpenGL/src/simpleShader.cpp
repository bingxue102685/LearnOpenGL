#include "simpleShader.h"

SimpleShader::SimpleShader()
{
	this->VAO = 0;
	this->shaderPorgram = 0;
	// Shaders1
	this->vertexShaderSource1 = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
	this->fragmentShaderSource1 = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

	// Shaders2
	this-> vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
	this->fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 color;\n"
	"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "color = ourColor;\n"
    "}\n\0";

	//初始化vao， shader
	this->initVAO();

	this->initShader();
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
   	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
void SimpleShader::initTriangleVAO()
{
		//设置顶点数据
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f,0.0f,
	};
	//生成顶点缓冲区对象
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//绑定缓冲区类型，一各缓冲区对象可以绑定多个缓冲区类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//把顶点数据复制到缓冲内存中。
	/*
	*GL_STATIC_DRAW ：数据不会或几乎不会改变。
	*GL_DYNAMIC_DRAW：数据会被改变很多。
	*GL_STREAM_DRAW ：数据每次绘制时都会改变
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//设置顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//解绑VAO
	glBindVertexArray(0);
}

void SimpleShader::initVAO()
{
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	GLuint indices[] = { // 起始于0!
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	GLuint VBO;
	GLuint EBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void SimpleShader::initShader()
{
	//创建顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &this->vertexShaderSource1, NULL);
	glCompileShader(vertexShader);

	//创建片段着色器
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &this->fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader);

	//链接着色器程序对象(Shader Program Object)
	//把着色器链接为一个程序就等于把每个着色器的输出链接到下一个着色器的输入

	this->shaderPorgram = glCreateProgram();
	glAttachShader(this->shaderPorgram, vertexShader);
	glAttachShader(this->shaderPorgram, fragmentShader);
	glLinkProgram(this->shaderPorgram);
	//删除无用着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void SimpleShader::render()
{
	//此处执行渲染操作
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->shaderPorgram);

	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(this->shaderPorgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}
