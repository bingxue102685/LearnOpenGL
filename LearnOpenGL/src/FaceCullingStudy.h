#ifndef _FACE_CULLING_STUDY_H_
#define _FACE_CULLING_STUDY_H_

#include "renderDelegate.h"
#include "StencilTestStudy.h"

class FaceCullingStudy: public Handle
{
public:
	FaceCullingStudy();
	void render();

private:
	StencilTestStudy* stencil;

};














#endif //_FACE_CULLING_STUDY_H_