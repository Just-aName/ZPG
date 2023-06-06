#pragma once
#include "DrawableObject.h"
#include "TextureManager.h"

class DrawableObjectTexture : public DrawableObject
{
protected:
	int textureID;
public:
	DrawableObjectTexture(Model* m, ShaderProgram* s, Transformation* t, int objectId, int textureID);

	void draw(Camera* camera) override;
};

