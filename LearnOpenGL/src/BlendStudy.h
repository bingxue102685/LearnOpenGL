#ifndef _BLEND_STUDY_H_
#define _BLEND_STUDY_H_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "StencilTestStudy.h"
#include <vector>
#include <map>
using namespace glm;
using namespace std;
class BlendStudy: public Handle
{
public:
	BlendStudy();
	void render();
private:
	GLuint grassTexture;
	GLuint grassVAO;
	void initVAO();
	void initTexture();
	StencilTestStudy* stencil;
	ShaderHandle* grassShader;
	void renderGrass1();
	void renderGrass2();
	vector<vec3> vegetation;
	map<float, vec3> sorted;
	void sortData();
	vec3 viewPostion;
};



#endif //_BLEND_STUDY_H_

