#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color, LightType type) : Light(type, ambient, diffuse, specular, color)
{
	this->position = position;
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}

PointLight::PointLight(const PointLight& l) : Light(l)
{
	this->position = l.getPosition();
	this->constantAttenuation = l.getConstantAttenuation();
	this->linearAttenuation = l.getLinearAttenuation();
	this->quadraticAttenuation = l.getQuadraticAttenuation();
}

glm::vec3 PointLight::getPosition() const
{
	return position;
}

float PointLight::getConstantAttenuation() const
{
	return constantAttenuation;
}

float PointLight::getLinearAttenuation() const
{
	return linearAttenuation;
}

float PointLight::getQuadraticAttenuation() const
{
	return constantAttenuation;
}


int PointLight::addLight(int index, int lightsCount, int shaderProgramID)
{
	int lCount = Light::addLight(index, lightsCount, shaderProgramID);

	std::string arrItem = "lights[" + std::to_string(index) + "]";

	GLint positionID = glGetUniformLocation(shaderProgramID, (arrItem + ".position").c_str());
	glUniform3f(positionID,
		position.x,
		position.y,
		position.z);

	GLint constantID = glGetUniformLocation(shaderProgramID, (arrItem + ".constant").c_str());
	glUniform1f(constantID, constantAttenuation);

	GLint linearID = glGetUniformLocation(shaderProgramID, (arrItem + ".linear").c_str());
	glUniform1f(constantID, linearAttenuation);

	GLint quadraticID = glGetUniformLocation(shaderProgramID, (arrItem + ".quadratic").c_str());
	glUniform1f(constantID, quadraticAttenuation);

	return lCount;
}