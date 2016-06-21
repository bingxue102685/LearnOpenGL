#ifndef _SHADER_HANDLER_
#define _SHADER_HANDLER_

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define FILE_PREFIX string("../resource/shaders/")

class ShaderHandle 
{
public:
	ShaderHandle(const char* fileName);
	GLuint getProgram();
	void UseProgram();
private:
	GLuint shaderProgram;
	void checkShaderCompileStatus(GLuint shader);
	void checkProgramLinkStatus(GLuint program);
};













#endif