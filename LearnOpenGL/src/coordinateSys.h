#ifndef _COORDINATE_SYS_
#define _COORDINATE_SYS_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;

class CoorDinateSys: public Handle
{
public:
	CoorDinateSys();
	void render();
	void render2();
private:
	ShaderHandle* shader;
	GLuint texture1;
	GLuint texture2;
	GLuint VAO;

	void initTexture();
	void initVAO();
	void initVAO2();
	vec3 cubePositions[10];

};









#endif 