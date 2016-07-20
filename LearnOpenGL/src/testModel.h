#ifndef _TEST_MODEL_H_
#define _TEST_MODEL_H_

#include "handle.h"
#include "shaderHandle.h"
#include "model.h"

class TestModel: public Handle
{
public:
	void render();
	TestModel();
private:
	ShaderHandle* shader;
	Model* model;
};







#endif //_TEST_MODEL_H_