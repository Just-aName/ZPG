#include "BlinnShaderProgram.h"

bool BlinnShaderProgram::set_view_direction()
{
	return set_matrix(this->observered_camera->getDirection(), "viewDirection");
}

bool BlinnShaderProgram::set_eye_position(glm::vec3& eyePosition)
{
	return set_matrix(eyePosition, "eyePosition");
}

bool BlinnShaderProgram::use_lights()
{
	return true;
}
