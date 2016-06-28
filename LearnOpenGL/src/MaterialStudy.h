#ifndef _MATERIAL_STUDY_
#define _MATERIAL_STUDY_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <hash_map>
using namespace glm;

class MaterialStudy:public Handle
{
public:
	MaterialStudy();
	void render();
	void render2();
private:
	GLuint cubeVAO;
	GLuint lightVAO;
	void initVAO();
	void initMaterialConfig();
	ShaderHandle* cubeShader;
	ShaderHandle* lightShader;
	hash_map<string, hash_map<string, vec3>> materials;
	string materialNames[24];
	int currentMatrialIndex;

};


#endif //_MATERIAL_STUDY_