#pragma once
#include "ShaderProgram.h"

class BlinnShaderProgram : public ShaderProgram
{
public:

	BlinnShaderProgram() : ShaderProgram("vertex_shader_blinn.txt", "fragment_shader_blinn.txt") {};

	bool set_view_direction() override;

	bool set_eye_position(glm::vec3& eyePosition) override;

	bool use_lights() override;
};

