#pragma once
#include "Model.h"

class ModelWithTexture : public Model
{
	VertexDataTexture* data;

public:
	ModelWithTexture(const float* points, int n);
	virtual ~ModelWithTexture();
	bool create_vao_vbo() override;
};

