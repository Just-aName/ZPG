#include "Light.h"
#include <iostream>

Light::Light(LightType type, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
{
	this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->color = color;
    this->type = type;
}

Light::Light(const Light& l)
{
	ambient = l.getAmbience();
	diffuse = l.getDiffussion();
	specular = l.getSpecular();
	color = l.getColor();
	type = l.getType();
}

glm::vec3 Light::getAmbience() const
{
	return ambient;
}

glm::vec3 Light::getDiffussion() const
{
	return diffuse;
}

glm::vec3 Light::getSpecular() const
{
	return specular;
}

const glm::vec3& Light::getColor() const
{
	return color;
}

const LightType Light::getType() const
{
	return type;
}

int Light::addLight(int index, int lightsCount, int shaderProgramID)
{
    GLint lightsCountID = glGetUniformLocation(shaderProgramID, "lightsCount");

    if (lightsCountID == -1)
    {
        std::cerr << "Missing iterator for lights ('lightsCount')" << std::endl;
        exit(1);
    }

    lightsCount += 1;

    glUniform1i(lightsCountID, lightsCount);
    std::string arrItem = "lights[" + std::to_string(index) + "]";

    GLint ambientID = glGetUniformLocation(shaderProgramID, (arrItem + ".ambient").c_str());
    glUniform3f(ambientID,
        ambient.x,
        ambient.y,
        ambient.z);

    GLint diffuseID = glGetUniformLocation(shaderProgramID, (arrItem + ".diffuse").c_str());
    glUniform3f(diffuseID,
        diffuse.x,
        diffuse.y,
        diffuse.z);

    GLint specularID = glGetUniformLocation(shaderProgramID, (arrItem + ".specular").c_str());
    glUniform3f(specularID,
        specular.x,
        specular.y,
        specular.z);

    GLint colorID = glGetUniformLocation(shaderProgramID, (arrItem + ".color").c_str());
    glUniform3f(colorID,
        color.x,
        color.y,
        color.z);

    GLint typeID = glGetUniformLocation(shaderProgramID, (arrItem + ".type").c_str());
    glUniform1i(typeID, (GLint)type);

    return lightsCount;
}
