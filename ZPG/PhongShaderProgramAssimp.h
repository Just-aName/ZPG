#pragma once
#include "PhongShaderProgramTexture.h"
class PhongShaderProgramAssimp :
    public PhongShaderProgramTexture
{
public:
    PhongShaderProgramAssimp() : PhongShaderProgramTexture("vertex_shader_phong_assimp.txt", "fragment_shader_phong_assimp.txt") {};
};

