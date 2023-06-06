#pragma once
#include "ConstantShaderProgramTexture.h"
class ConstantShaderProgramSkyBox :
    public ConstantShaderProgramTexture
{
public:
    ConstantShaderProgramSkyBox() : ConstantShaderProgramTexture("vertex_shader_skybox.txt", "fragment_shader_skybox.txt") {};
};

