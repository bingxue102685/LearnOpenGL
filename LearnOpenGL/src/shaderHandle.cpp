#include "shaderHandle.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

ShaderHandle::ShaderHandle(const char* fileName)
{
	string vextexSource;
	string fragmentSource;

	string fullVsPath("");
	string fullFragPath("");

	fullVsPath += FILE_PREFIX;
	fullFragPath += FILE_PREFIX;

	fullVsPath += fileName;
	fullFragPath += fileName;

	fullVsPath += ".vs";
	fullFragPath += ".frag";

	ifstream vsReadFile;
	ifstream fragReadFile;

	vsReadFile.open(fullVsPath);
	fragReadFile.open(fullFragPath);
	
	stringstream vsTempReadString, fragTempReadString;
	vsTempReadString << vsReadFile.rdbuf();
	fragTempReadString << fragReadFile.rdbuf();

	vsReadFile.close();
	fragReadFile.close();

	vextexSource = vsTempReadString.str();
	fragmentSource = fragTempReadString.str();

	const GLchar* vextexCode = vextexSource.c_str();
	const GLchar* fragmentCode = fragmentSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vextexCode, NULL);
	glCompileShader(vertexShader);
	this->checkShaderCompileStatus(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	this->checkShaderCompileStatus(fragmentShader);

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
	this->checkProgramLinkStatus(this->shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
}

void ShaderHandle::checkShaderCompileStatus(GLuint shader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderHandle::checkProgramLinkStatus(GLuint program)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderHandle::UseProgram()
{
	glUseProgram(this->shaderProgram);
}

GLuint ShaderHandle::getProgram()
{
	return this->shaderProgram;
}
