#include "Spotlight.h"


Spotlight::Spotlight(glm::vec3 position, glm::vec3 direction, float spotCutOff, float spotOuterCutOff, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color) : PointLight(position, constantAttenuation, linearAttenuation, quadraticAttenuation, ambient, diffuse, specular, color, LightType::SPOTLIGHT)
{
	this->direction = direction;
	this->spotCutOff = cos(radians(spotCutOff));
	this->spotOuterCutOff = cos(radians(spotOuterCutOff));
}

Spotlight::Spotlight(const Spotlight& l) : PointLight(l)
{
	direction = l.getDirection();
	spotCutOff = l.getSpotCutOff();
	spotOuterCutOff = l.getSpotOuterCutOff();
}

glm::vec3 Spotlight::getDirection() const
{
	return direction;
}

float Spotlight::getSpotCutOff() const
{
	return spotCutOff;
}

float Spotlight::getSpotOuterCutOff() const
{
	return spotOuterCutOff;
}

int Spotlight::addLight(int index, int lightsCount, int shaderProgramID)
{
    int lCount = PointLight::addLight(index, lightsCount, shaderProgramID);

    std::string arrItem = "lights[" + std::to_string(index) + "]";

    GLint directionID = glGetUniformLocation(shaderProgramID, (arrItem + ".direction").c_str());
    glUniform3f(directionID,
        direction.x,
        direction.y,
        direction.z);

    GLint spotCutOffID = glGetUniformLocation(shaderProgramID, (arrItem + ".spotCutOff").c_str());
    glUniform1f(spotCutOffID, spotCutOff);

    GLint spotOuterCutOffID = glGetUniformLocation(shaderProgramID, (arrItem + ".spotOuterCutOff").c_str());
    glUniform1f(spotOuterCutOffID, spotOuterCutOff);

    return lCount;
}
