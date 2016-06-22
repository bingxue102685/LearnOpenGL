#ifndef _CAMERA_STUDY_
#define _CAMERA_STUDY_


#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <SOIL\SOIL.h>
#include "Camera.h"

using namespace glm;

class CameraStudy: public Handle
{
public:
	CameraStudy();
	void render();
private:
	ShaderHandle* shader;
	GLuint VAO;
	GLuint texture;
	vec3 cubePositions[10];
	Camera* camera;
private:
	void initParameters();
	void initStatues();
	void InitVAO();
	void InitTexture();	
};








#endif //_CAMERA_STUDY_