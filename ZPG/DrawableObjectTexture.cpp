#include "DrawableObjectTexture.h"

DrawableObjectTexture::DrawableObjectTexture(Model* m, ShaderProgram* s, Transformation* t, int objectId, int textureID) : DrawableObject(m, s, t, objectId)
{
	this->textureID = textureID;
}

void DrawableObjectTexture::draw(Camera* camera)
{
	if (!shader->set_uniform_number(textureID, "textureUnitID"))
	{
		std::cerr << "WARNING: Variable 'textureUnitID' not found in fragment shader" << std::endl;
		exit(1);
	}

	DrawableObject::draw(camera);
}
