#pragma once
#include "ShaderProgram.h"

class LambertShaderProgram : public ShaderProgram
{
public:
	LambertShaderProgram() : ShaderProgram("vertex_shader_lambert.txt", "fragment_shader_lambert.txt") {};

	bool set_view_direction() override;

	bool set_eye_position(glm::vec3& eyePosition) override;

	bool use_lights() override;
};

