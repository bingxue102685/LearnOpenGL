#ifndef _STENCIL_TEST_STUDY_H_
#define _STENCIL_TEST_STUDY_H_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class StencilTestStudy:public Handle
{
public:
	StencilTestStudy();
	void render();
private:
	GLuint planeVAO;
	GLuint boxVAO;
	GLuint planeTexture;
	GLuint boxTexture;
	ShaderHandle* borderShader;
	ShaderHandle* boxShader;
	void initVAO();
	void initTexture();




};






#endif //_STENCIL_TEST_STUDY_H_