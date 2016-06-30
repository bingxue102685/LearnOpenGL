#ifndef _LIGHTING_MAP_STUDY_
#define _LIGHTING_MAP_STUDY_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class LightingMapStudy:public Handle
{
public:
	LightingMapStudy();
	void render();
private:
	GLuint lightVAO;
	GLuint cubeVAO;
	GLuint cubeDiffuseTexture;
	GLuint cubeSpecularTexture;
	GLuint cubeEmissionTexture;
	ShaderHandle* lightShader;
	ShaderHandle* cubeShader;
	vec3 cubePositions[10];
	void initVAO();
	void initTexture();

	


};

#endif // _LIGHTING_MAP_STUDY_