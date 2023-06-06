#include "LambertShaderProgram.h"

bool LambertShaderProgram::set_view_direction()
{
	return set_matrix(this->observered_camera->getDirection(), "viewDirection");
}

bool LambertShaderProgram::set_eye_position(glm::vec3& eyePosition)
{
	return true;
}

bool LambertShaderProgram::use_lights()
{
	return true;
}
