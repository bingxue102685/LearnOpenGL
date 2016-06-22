#ifndef _MATERIAL_STUDY_
#define _MATERIAL_STUDY_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class MaterialStudy:public Handle
{
public:
	MaterialStudy();
	void render();
private:
	GLuint cubeVAO;
	GLuint lightVAO;
	void initVAO();
	ShaderHandle* cubeShader;
	ShaderHandle* lightShader;

};


#endif //_MATERIAL_STUDY_