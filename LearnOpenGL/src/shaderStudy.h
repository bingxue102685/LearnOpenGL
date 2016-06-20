#ifndef _SHADER_STUDY_
#define _SHADER_STUDY_

#include "renderDelegate.h"
#include "shaderHandle.h"
class ShaderStudy: public Handle
{
public:
	ShaderStudy();
	void render();
private:
	GLchar* vertexResource;
	GLchar* fragmentResource;
	GLuint shaderProgram;
	GLuint VAO;
	GLuint transform;
	ShaderHandle* shader;
private:
	void initVAO();
};






#endif _SHADER_STUDY_