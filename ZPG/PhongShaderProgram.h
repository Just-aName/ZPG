#pragma once
#include "ShaderProgram.h"

class PhongShaderProgram : public ShaderProgram
{
public:

	PhongShaderProgram() : ShaderProgram("vertex_shader_phong.txt", "fragment_shader_phong.txt") {};

	PhongShaderProgram(const char* vert, const char* frag) : ShaderProgram(vert, frag) {};

	bool set_view_direction() override;

	bool set_eye_position(glm::vec3& eyePosition) override;
	
	bool use_lights() override;
};

