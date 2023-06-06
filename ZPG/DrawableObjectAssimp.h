#pragma once
#include "DrawableObjectTexture.h"

class DrawableObjectAssimp :
    public DrawableObjectTexture
{
protected:
    int normalID = 0;
public:
    DrawableObjectAssimp(Model* m, ShaderProgram* s, Transformation* t, int objectId, int textureID, int normalID);

    void draw(Camera* camera) override;
};

