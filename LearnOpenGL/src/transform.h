#ifndef _TRANSFORM_
#define _TRANSFORM_

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "renderDelegate.h"
#include "shaderHandle.h"

using namespace glm;

class Transform: public Handle
{
public:
	Transform();
	void render();
private:
	GLuint VAO;
	GLuint texture1;
	GLuint texture2;
	ShaderHandle* shader;
	mat4 trans;

	void initVAO();
	void initTexture();
	void initMatrix();
};













#endif //_TRANSFORM_