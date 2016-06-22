#ifndef _BASIC_LIGHTING_
#define _BASIC_LIGHTING_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class BasicLighting:public Handle
{
public:
	BasicLighting();
	~BasicLighting();
	void render();

private:
	GLuint ColorVAO;
	GLuint LightVAO;
	ShaderHandle* colorShader;
	ShaderHandle* lightShader;
	void initVAO();

};



#endif //_COLOR_STUDY_