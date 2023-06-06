#pragma once
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

#include "ShaderLoader.h"
#include "Camera.h"
#include "Observer.h"

class Camera;
class ShaderProgram : public Observer, public ShaderLoader
{
protected:
	GLint uniformLocationID = -1;
	Camera* observered_camera = nullptr;
public:
	ShaderProgram();
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	virtual ~ShaderProgram();

	bool set_program();

	bool set_matrix(glm::mat4 modelMatrix, const char* variableName);
	
	bool set_matrix(glm::vec3 modelMatrix, const char* variableName);

	bool set_uniform_number(int number, const char* variableName);

	void update();

	//void update(glm::mat4& changed_matrix_value, std::string& changed_matrix_name);

	void set_observed_camera(Camera* c);

	virtual bool set_view_direction();

	virtual bool set_eye_position(glm::vec3& eyePosition);

	virtual bool use_lights();

	int get_shader_id();
};