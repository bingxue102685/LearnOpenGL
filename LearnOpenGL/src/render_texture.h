#ifndef _RENDER_TEXTURE_
#define _RENDER_TEXTURE_

#include "renderDelegate.h"
#include  "SOIL/SOIL.h"
#include "shaderHandle.h"

class RenderTexture: public Handle 
{
public:
	RenderTexture();
	void render();
private:
	ShaderHandle* shader;
	GLuint texture1;
	GLuint texture2;
	GLuint VAO;
	void initVAO();
	void initTexture();
};







#endif //_RENDER_TEXTURE_