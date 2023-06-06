#pragma once
#include "Light.h"

class DirectionLight : public Light
{
private:
	glm::vec3 direction;

public:
	DirectionLight(glm::vec3 direction, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f));
	DirectionLight(const DirectionLight&);

	glm::vec3 getDirection() const;

	int addLight(int index, int lightsCount, int shaderProgramID) override;
};
