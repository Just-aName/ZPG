#pragma once
#include "Model.h"
class ModelPlain : public Model
{
	Point* data;

public:
	ModelPlain(const float* points, int n);
	virtual ~ModelPlain();
	bool create_vao_vbo() override;
};

