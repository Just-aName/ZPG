#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Light.h"

class DrawableObject
{
public:
	int id;
	ShaderProgram* shader;
	Model* model;
	Transformation* transformation;
public:
	DrawableObject(Model* m, ShaderProgram* s, Transformation* t, int objectId);
	virtual ~DrawableObject();
	bool create_vao_vbo();
	void set_shader(ShaderProgram* sh = nullptr);
	virtual void draw(Camera* camera);
	void set_trans_matrix(Transformation* tr);
	bool use_lights();
};

