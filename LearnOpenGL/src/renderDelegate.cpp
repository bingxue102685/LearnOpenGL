#include "renderDelegate.h"

RenderDelegate* RenderDelegate::delegateSingleton = nullptr;

RenderDelegate::RenderDelegate()
{
	handleDelegate = nullptr;
	window = nullptr;

	if (this->initWindow() == -1) {
		cout << "Windows initialize failure!" << endl;
	}
}

void RenderDelegate::render()
{
	if (this->handleDelegate != nullptr) {
		glEnable(GL_DEPTH_TEST);
		this->handleDelegate->render();
	} else {
		cout << "Not initialize handleDelegate!" << endl;
	}
}
void RenderDelegate::setHandleDelegate(Handle* handleDelegate)
{
	this->handleDelegate = handleDelegate;
}


int RenderDelegate::initWindow()
{
	//glfw初始化
	glfwInit();
	//设置OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	//设置OpenGL的次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//使用OpenGL的核心组件（无法使用已经废弃的OpenGL api）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//窗口不允许改变
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//创建窗口， glfwCreateWindow（int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share）
	this->window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (this->window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//官方文档：在当前线程中创建指定窗口的OpenGL上下文，一次只能在一个线程上创建一个上下文，而且每个线程一次只能有一个上下文
	glfwMakeContextCurrent(this->window);

	//初始化glew	
	//glewExperimental设置为GL_TRUE，更多的使用现代化技术（没有文档，只能照抄教程的）
	glewExperimental = GL_TRUE;
	//初始化glew
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" <<std::endl;
		return -1;
	}
	//指定窗口的左下位置，宽高
	glViewport(0, 0, 800, 600);
	return 1;
}

GLFWwindow* RenderDelegate::getWindowHandle()
{
	return this->window;
}

void RenderDelegate::run() {

	//函数在我们每次循环的开始前检查一次GLFW是否准备好要退出
	while(!glfwWindowShouldClose(this->window)) {
		//检查有没有什么事件发生（鼠标，键盘），并调用对应的函数
		glfwPollEvents();
		//此处执行渲染操作
		this->render();
		//交换缓冲区
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}

RenderDelegate* RenderDelegate::getInstance()
{
	if (RenderDelegate::delegateSingleton == nullptr) {
		RenderDelegate::delegateSingleton = new RenderDelegate();
	}

	return RenderDelegate::delegateSingleton;
}

