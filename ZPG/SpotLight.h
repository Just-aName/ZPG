#pragma once
#include "PointLight.h"
#include <glm/trigonometric.hpp>

using glm::radians;

class Spotlight : public PointLight
{
private:
	glm::vec3 direction;
	float spotCutOff;
	float spotOuterCutOff;

public:
	Spotlight(glm::vec3 position, glm::vec3 direction, float spotCutOff = 12.5f, float spotOuterCutOff = 17.5f, float constantAttenuation = 1.0f, float linearAttenuation = .0f, float quadraticAttenuation = .0f, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f));
	Spotlight(const Spotlight&);

	glm::vec3 getDirection() const;
	float getSpotCutOff() const;
	float getSpotOuterCutOff() const;

	int addLight(int index, int lightsCount, int shaderProgramID) override;
};

