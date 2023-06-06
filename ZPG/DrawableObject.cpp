#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* m, ShaderProgram* s, Transformation* t, int objectId)
{
	this->id = objectId;
	this->model = m;
	this->shader = s;
	this->transformation = t;
}

DrawableObject::~DrawableObject()
{
	if (model != nullptr)
		delete model;
	if (shader != nullptr)
		//delete shader;
	if (transformation != nullptr)
		delete transformation;
}

bool DrawableObject::create_vao_vbo()
{
	return model->create_vao_vbo();
}

void DrawableObject::set_shader(ShaderProgram* sh)
{
	if (sh != nullptr && this->shader == nullptr)
	{
		this->shader = sh;
	}
	if (!shader->set_program())
	{
		fprintf(stderr, "Shader program wasn't compiled with success \n");
		exit(-1);
	}
}
void DrawableObject::draw(Camera* camera)
{
	shader->set_observed_camera(camera);

	if (!shader->set_matrix(transformation->get_matrix(), "modelMatrix"))
	{
		fprintf(stderr, "Error while setting variable modelMatrix");
		exit(-1);
	}

	if (!shader->set_view_direction())
	{
		fprintf(stderr, "Error while setting variable viewDirection");
		exit(-1);
	}

	if (!shader->set_eye_position(camera->getEye()))
	{
		fprintf(stderr, "Error while setting variable eyePosition");
		exit(-1);
	}

	glStencilFunc(GL_ALWAYS, id, 0xFF);
	this->model->draw();
}

void DrawableObject::set_trans_matrix(Transformation* tr)
{
	this->transformation = tr;
}

bool DrawableObject::use_lights()
{
	return shader->use_lights();
}
