#ifndef _CUB_MAP_STUDY_H_
#define _CUB_MAP_STUDY_H_


#include "renderDelegate.h"
#include "shaderHandle.h"
#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;
using namespace std;

class CubmapStudy:public Handle
{
public:
	CubmapStudy();
	void render();
private:
	GLuint textureID;
	GLuint cubeTexture;
	ShaderHandle* skyboxShader;
	ShaderHandle* cubeShader;
	GLuint skyboxVAO;
	GLuint cubeVAO;
	Camera* camera;
	void initTexture();
	void initVAO();
};






#endif //_CUB_MAP_STUDY_H_