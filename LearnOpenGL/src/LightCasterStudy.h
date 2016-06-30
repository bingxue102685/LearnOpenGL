#ifndef _LIGHT_CASTER_STUDY_
#define _LIGHT_CASTER_STUDY_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;


class LightCasterStudy:public Handle
{
public:
	LightCasterStudy();
	void render();
private:
	GLuint cubeVAO;
	GLuint lightVAO;
	GLuint cubeDiffuseTexture;
	GLuint cubeSpecularTexture;
	ShaderHandle* cubeShader;
	ShaderHandle* lightShader;
	vec3 cubePositions[10];
	void initVAO();
	void initTexture();
};

















#endif //_LIGHT_CASTER_STUDY_