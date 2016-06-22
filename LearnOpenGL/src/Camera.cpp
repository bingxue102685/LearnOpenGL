#include "Camera.h"

vec3 Camera::cameraPos = vec3(0.0f, 0.0f, -3.0f);
vec3 Camera::cameraFront = vec3(0.0f, 0.0f, 3.0f);
vec3 Camera::cameraUp = vec3(0.0f, 1.0f, 0.0f);
bool Camera::keys[1024];
GLfloat Camera::lastX = 400;
GLfloat Camera::lastY = 300;
GLfloat Camera::pitchValue = 0;
GLfloat Camera::yawValue = 0;
GLboolean Camera::firstMouse = GL_TRUE;
GLfloat Camera::aspect = 55.0f;

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}
	
	if(action == GLFW_PRESS)
		Camera::keys[key] = true;
	else if(action == GLFW_RELEASE)
		Camera::keys[key] = false;	
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (Camera::firstMouse)
	{
		Camera::lastX = xpos;
		Camera::lastY = ypos;
		Camera::firstMouse = GL_FALSE;
	}

	//1.计算出鼠标和上一帧的偏移量
	GLfloat xOffset = xpos - Camera::lastX;
	GLfloat yOffset = ypos - Camera::lastY;
	Camera::lastX = xpos;
	Camera::lastY = ypos;
	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;
	//2.把偏移量添加到摄像机的俯仰角和偏航角
	Camera::yawValue += xOffset;
	Camera::pitchValue += yOffset;
	//3.对俯仰角进行最大最小限制
	if (Camera::pitchValue > 89.0) {
		Camera::pitchValue = 89.0;
	}

	if (Camera::pitchValue < -89.0) {
		Camera::pitchValue = -89.0;
	}
	//4.计算方向向量
	vec3 frontTemp;
	frontTemp.x = cos(radians(Camera::pitchValue)) * cos(radians(Camera::yawValue));
	frontTemp.y = sin(radians(Camera::pitchValue));
	frontTemp.z = cos(radians(Camera::pitchValue)) * sin(radians(Camera::yawValue));
	Camera::cameraFront = normalize(frontTemp);
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (Camera::aspect >= 1.0f && Camera::aspect <= 55.0f)
	{
		Camera::aspect -= yoffset;
	}

	if (Camera::aspect < 1.0f)
	{
		Camera::aspect = 1.0f;
	}

	if (Camera::aspect > 55.0f)
	{
		Camera::aspect = 55.0f;
	}
}

void Camera::DoMovement()
{
	GLfloat cameraSpeed = 0.1f * this->deltaTime;
	if (Camera::keys[GLFW_KEY_W])
	{
		Camera::cameraPos += (Camera::cameraFront * cameraSpeed);
	}
	
	if (Camera::keys[GLFW_KEY_S])
	{
		Camera::cameraPos -= (Camera::cameraFront * cameraSpeed);
	}

	if (Camera::keys[GLFW_KEY_A])
	{
		Camera::cameraPos -= (normalize(cross(Camera::cameraFront, Camera::cameraUp)) * cameraSpeed);
	}

	if (Camera::keys[GLFW_KEY_D])
	{
		Camera::cameraPos += (normalize(cross(Camera::cameraFront, Camera::cameraUp)) * cameraSpeed);
	}
	
}

mat4 Camera::GetLookAt()
{
	//                  摄像机的位置，          摄像机指向的位置  ，     摄像机上方向
	return lookAt(Camera::cameraPos, Camera::cameraPos + Camera::cameraFront, Camera::cameraUp);
}

void Camera::setDeltaTime(GLfloat currentTime)
{
	this->deltaTime = currentTime - this->lastTime;
	this->lastTime = currentTime;
}