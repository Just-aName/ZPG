#include "DrawableObjectAssimp.h"

DrawableObjectAssimp::DrawableObjectAssimp(Model* m, ShaderProgram* s, Transformation* t, int objectId, int textureID, int normalID) : DrawableObjectTexture(m,s,t,objectId, textureID)
{
	this->normalID = normalID;
}


void DrawableObjectAssimp::draw(Camera* camera)
{
	if (!shader->set_uniform_number(normalID, "normalMapUnitID"))
	{
		std::cerr << "WARNING: Variable 'textureUnitID' not found in fragment shader" << std::endl;
		exit(1);
	}
	DrawableObjectTexture::draw(camera);
}
