#include "DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color) : Light(LightType::DIRECTIONAL, ambient, diffuse, specular, color)
{
    this->direction = direction;
}

DirectionLight::DirectionLight(const DirectionLight& l) : Light(l)
{
	direction = l.getDirection();
}

glm::vec3 DirectionLight::getDirection() const
{
	return direction;
}

int DirectionLight::addLight(int index, int lightsCount, int shaderProgramID)
{
    int lCount = Light::addLight(index, lightsCount, shaderProgramID);

    GLint directionID = glGetUniformLocation(shaderProgramID, ("lights[" + std::to_string(index) + "].direction").c_str());
    glUniform3f(directionID,
        direction.x,
        direction.y,
        direction.z);
    return lCount;
}
