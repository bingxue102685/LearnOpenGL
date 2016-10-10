#ifndef CUB_MAP_STUDY_R_H
#define CUB_MAP_STUDY_R_H

#include "renderDelegate.h"
#include "shaderHandle.h"
#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>



class CubMapStudyR: public Handle
{
public:
	CubMapStudyR();
	void render();
	void renderCubeFirst();
	void renderSkyBoxFirst();
	void renderReflect();
private:
	GLuint skyBoxTextureID;
	GLuint cubeTexutrueID;
	GLuint skyBoxVAO;
	GLuint cubeVAO;
	ShaderHandle* skyboxShader;
	ShaderHandle* cubeShader;
	Camera* camera;
private:
	void initTextrueID();
	void initVAO();
};
















#endif //CUB_MAP_STUDY_R_H