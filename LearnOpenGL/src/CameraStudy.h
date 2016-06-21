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
	GLfloat deltaTime;
	GLfloat lastTime;

	static vec3 cameraPos;
	static vec3 cameraFront;
	static vec3 cameraUp;
	static bool keys[1024];
	static GLfloat lastX;
	static GLfloat lastY;
	static GLfloat pitchValue; //俯视角
	static GLfloat yawValue; //偏航角
	static GLboolean firstMouse;  //是否第一次移动鼠标，防止第一次进入页面，摄像机跳动过大
	static GLboolean firstScroll; //是否第一次滚动滑轮
	static GLfloat aspect;

private:
	void initParameters();
	void initStatues();
	void InitVAO();
	void InitTexture();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void DoMovement();
	
};








#endif //_CAMERA_STUDY_