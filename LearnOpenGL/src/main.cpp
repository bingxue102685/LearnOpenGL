/*
	äÖÈ¾²½Öè£º1.ÉèÖÃäÖÈ¾´úÀísetHandleDelegate
			 2. run()

*/

#define GLEW_STATIC
#include "renderDelegate.h"
#include "simpleShader.h"
#include "shaderStudy.h"
#include "render_texture.h"
#include "transform.h"
#include "coordinateSys.h"
#include "CameraStudy.h"
#include "ColorStudy.h"
int main() 
{
	RenderDelegate* renderDelegate = RenderDelegate::getInstance();

	renderDelegate->setHandleDelegate(new ColorStudy());

	renderDelegate->run();

	return 0;
}
