/*
	注：此类为一简单代理类
*/

#ifndef _RENDER_DELEGATE_
#define _RENDER_DELEGATE_

#include <iostream>
#include "handle.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;


class RenderDelegate: public Handle
{
	
public:
	void run();
	void render();
	GLFWwindow* getWindowHandle();
	void printProgramInfoLog(GLuint obj);
	void setHandleDelegate(Handle* handleDelegate);
	static RenderDelegate* getInstance();
private:
	Handle* handleDelegate;
	GLFWwindow* window;
	static RenderDelegate* delegateSingleton;
private:
	RenderDelegate();
	int initWindow();
	void initVAO();
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};


#endif