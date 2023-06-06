#pragma once
#include "ShaderProgram.h"

class ConstantShaderProgram : public ShaderProgram
{
public:
	ConstantShaderProgram() : ShaderProgram("vertex_shader_constant.txt", "fragment_shader_constant.txt") {};

	ConstantShaderProgram(const char* vert, const char* frag) : ShaderProgram(vert, frag) {};

};

