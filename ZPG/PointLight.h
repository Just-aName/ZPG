#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
	glm::vec3 position;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

public:
	PointLight(glm::vec3 position, float constantAttenuation = 1.0f, float linearAttenuation = .0f, float quadraticAttenuation = .0f, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f), LightType type = LightType::POINT);
	PointLight(const PointLight&);

	glm::vec3 getPosition() const;
	float getConstantAttenuation() const;
	float getLinearAttenuation() const;
	float getQuadraticAttenuation() const;

	int addLight(int index, int lightsCount, int shaderProgramID) override;
};