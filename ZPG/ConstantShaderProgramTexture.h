#pragma once
#include "ConstantShaderProgram.h"

class ConstantShaderProgramTexture : public ConstantShaderProgram
{
public:
	ConstantShaderProgramTexture() : ConstantShaderProgram("vertex_shader_constant_texture.txt", "fragment_shader_constant_texture.txt") {};

	ConstantShaderProgramTexture(const char* vert, const char* frag) : ConstantShaderProgram(vert, frag) {};


};

