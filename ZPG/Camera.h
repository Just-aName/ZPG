#pragma once
#include "ShaderProgram.h"


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
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "Subject.h"

class ShaderProgram;
class Camera : public Subject
{
	glm::vec3 eye;
	glm::vec3 direction;
	glm::vec3 up;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float mouseSpeed = 30.0f;
	float moveSpeed = 0.2f;

	std::string matrixNewName = std::string();
	glm::mat4 matrixNewValue = glm::mat4(1.0f);
	//std::vector<ShaderProgram*> shaders;

public:
	Camera(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition = glm::vec3(0,0,0));
	~Camera();

	glm::vec3& getEye();
	glm::vec3& getDirection();
	glm::mat4& getCamera();
	glm::mat4& get_projection_matrix();
	glm::mat4& get_view_matrix();

	void frontMove();
	void rightMove();
	void backMove();
	void leftMove();
	void setMoveSpeed(float newMoveSpeed);
	void mouseMove(double x, double y, int width, int height);

	void attach_shader(ShaderProgram* shader);
	bool search_shader(ShaderProgram* shader);
	void unsubscribe_shader(ShaderProgram* shader);
	void set_changed_values(glm::mat4& matrixNewValue, std::string matrixNewName);
	void resize_projection(float width, float height);

	//void notify();
	void update();
};

