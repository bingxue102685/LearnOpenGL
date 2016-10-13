#ifndef ADVANCED_GLSL_STUDY_H
#define ADVANCED_GLSL_STUDY_H

#include "renderDelegate.h"
#include "shaderHandle.h"
#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class AdvancedGLSLStudy:public Handle
{
public:
	AdvancedGLSLStudy();
	void render();
private:
	void renderPoint();
	void renderFrogCoord();
	void renderUBO();
	void initVAO();
	void initUBO();
	ShaderHandle* pointShader;
	ShaderHandle* fragCoordShader;
	ShaderHandle* redShader;
	ShaderHandle* greenShader;
	ShaderHandle* blueShader;
	ShaderHandle* yellowShader;
	GLuint pointVAO;

};

#endif //ADVANCED_GLSL_STUDY_H