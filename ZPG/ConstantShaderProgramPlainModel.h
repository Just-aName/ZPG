#pragma once
#include "ConstantShaderProgramTexture.h"
class ConstantShaderProgramPlainModel :
    public ConstantShaderProgramTexture
{
public:
    ConstantShaderProgramPlainModel() : ConstantShaderProgramTexture("vertex_shader_constant_plain_model.txt", "fragment_shader_constant_plain_model.txt") {};
};

