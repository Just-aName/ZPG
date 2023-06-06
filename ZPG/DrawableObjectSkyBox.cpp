#include "DrawableObjectSkyBox.h"

DrawableObjectSkyBox::DrawableObjectSkyBox(Model* m, ShaderProgram* s, Transformation* t, int objectId, int textureID) : DrawableObjectTexture(m, s, t, objectId, textureID)
{
}

void DrawableObjectSkyBox::draw(Camera* camera)
{
	shader->set_observed_camera(camera);

	glm::mat4 M0 = glm::mat4(1.0f);
	M0 = glm::translate(M0, camera->getEye());
	delete transformation;
	transformation = new Transformation(M0);

	if (!shader->set_matrix(transformation->get_matrix(), "modelMatrix"))
	{
		fprintf(stderr, "Error while setting variable modelMatrix");
		exit(-1);
	}

	if (!shader->set_uniform_number(textureID, "textureUnitID"))
	{
		fprintf(stderr, "Error while setting variable textureUnitID");
		exit(-1);
	}

	this->model->draw();
	glClear(GL_DEPTH_BUFFER_BIT);
	
}
