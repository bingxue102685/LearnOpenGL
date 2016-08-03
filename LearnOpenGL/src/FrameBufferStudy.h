#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include "renderDelegate.h"
#include "shaderHandle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;
using namespace std;


class FrameBufferStudy: public Handle
{
public:
	FrameBufferStudy();
	void render();
private:
	GLuint frameBuffer;
	GLuint textureColorBuffer;
	GLuint rbo;
	GLuint floorTexture;
	GLuint cubeTexture;
	GLuint floorVAO;
	GLuint cubeVAO;
	GLuint quadVAO;
	void initFBO();
	void initVAO();
	GLuint generateTexture(const char* fileName, bool isTransparent);
	ShaderHandle* shader;
	ShaderHandle* quadShader;




};








#endif //_FRAME_BUFFER_H_