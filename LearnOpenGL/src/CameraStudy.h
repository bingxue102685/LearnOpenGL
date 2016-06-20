#ifndef _CAMERA_STUDY_
#define _CAMERA_STUDY_


#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <SOIL\SOIL.h>

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
	static vec3 cameraPos;
	static vec3 cameraFront;
	static vec3 cameraUp;
	static bool keys[1024];
	GLfloat deltaTime;
	GLfloat lastTime;
	void initStatues();
	void InitVAO();
	void InitTexture();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void DoMovement();
	
};








#endif //_CAMERA_STUDY_