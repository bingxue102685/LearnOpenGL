#include "FaceCullingStudy.h"


FaceCullingStudy::FaceCullingStudy()
{
	stencil = new StencilTestStudy();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	/*
	GL_BACK：只剔除背面。
	GL_FRONT：只剔除正面。
	GL_FRONT_AND_BACK：剔除背面和正面。
	*/
	glFrontFace(GL_CCW);
	//默认值是GL_CCW，它代表逆时针，GL_CW代表顺时针顺序。
}



void FaceCullingStudy::render()
{
	//面剔除，可提高渲染性能，至少提高50%,顶点的顺序最好设置为逆时针
	stencil->render();
}