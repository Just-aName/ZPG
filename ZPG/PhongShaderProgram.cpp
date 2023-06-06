#include "PhongShaderProgram.h"

bool PhongShaderProgram::set_view_direction()
{
	return set_matrix(this->observered_camera->getDirection(), "viewDirection");
}

bool PhongShaderProgram::set_eye_position(glm::vec3& eyePosition)
{
	return set_matrix(eyePosition, "eyePosition");
}

bool PhongShaderProgram::use_lights()
{
	return true;
}
