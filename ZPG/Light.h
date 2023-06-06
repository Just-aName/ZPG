#pragma once
#include <string>

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


enum class LightType
{
	POINT,
	DIRECTIONAL,
	SPOTLIGHT
};

class Light
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec3 color;
	LightType type;

public:
	Light(LightType type, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f));
	Light(const Light&);

	glm::vec3 getAmbience() const;
	glm::vec3 getDiffussion() const;
	glm::vec3 getSpecular() const;

	const glm::vec3& getColor() const;
	const LightType getType() const;

	virtual int addLight(int index, int lightsCount, int shaderProgramID);
};

