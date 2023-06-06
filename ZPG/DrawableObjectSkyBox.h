#pragma once
#include "DrawableObjectTexture.h"
class DrawableObjectSkyBox :
    public DrawableObjectTexture
{
public:
	DrawableObjectSkyBox(Model* m, ShaderProgram* s, Transformation* t, int objectId, int textureID);

	void draw(Camera* camera) override;
};

