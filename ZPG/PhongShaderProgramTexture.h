#pragma once
#include "PhongShaderProgram.h"

class PhongShaderProgramTexture : public PhongShaderProgram
{
public:
	PhongShaderProgramTexture() : PhongShaderProgram("vertex_shader_phong_texture.txt", "fragment_shader_phong_texture.txt") {};
	PhongShaderProgramTexture(const char* vert, const char* frag) : PhongShaderProgram(vert, frag) {};
};

