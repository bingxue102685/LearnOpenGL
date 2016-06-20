#ifndef _SIMPLE_SHADER_
#define _SIMPLE_SHADER_

#include "renderDelegate.h"

class SimpleShader: public Handle
{
public:
	void render();
	SimpleShader();
private:
	const GLchar* vertexShaderSource1;
	const GLchar* fragmentShaderSource1;
	const GLchar* vertexShaderSource2;
	const GLchar* fragmentShaderSource2;

	GLuint VAO;
	GLuint shaderPorgram;
private:
	void initTriangleVAO();
	void initVAO();
	void initShader();
	
};





#endif //_SIMPLE_SHADER_