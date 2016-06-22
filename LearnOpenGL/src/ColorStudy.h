#ifndef _COLOR_STUDY_
#define _COLOR_STUDY_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

class ColorStudy:public Handle
{
public:
	ColorStudy();
	~ColorStudy();
	void render();

private:
	GLuint ColorVAO;
	GLuint LightVAO;
	ShaderHandle* colorShader;
	ShaderHandle* lightShader;
	void initVAO();

};



#endif //_COLOR_STUDY_