#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
	this->loadShader("vertex_shader_constant.txt", "fragment_shader_constant.txt");
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
	this->loadShader(vertexFile, fragmentFile);
}

ShaderProgram::~ShaderProgram()
{
	this->observered_camera->unsubscribe_shader(this);
	this->observered_camera = nullptr;
}

bool ShaderProgram::set_program()
{
	if (this->shaderProgramID != -1)
	{
		glUseProgram(this->shaderProgramID);
		return true;
	}
	else
	{
		bool res = this->loadShader("vertex_shader_constant.txt", "fragment_shader_constant.txt");
		glUseProgram(this->shaderProgramID);
		return res;
	}
}

bool ShaderProgram::set_matrix(glm::mat4 modelMatrix, const char* variableName)
{
	uniformLocationID = glGetUniformLocation(this->shaderProgramID, variableName);
	if (uniformLocationID == -1)
	{
		fprintf(stderr, "Variable %s location was not found \n", variableName);
		exit(-1);
	}
	glUniformMatrix4fv(uniformLocationID, 1, GL_FALSE, &modelMatrix[0][0]);

	return true;
}

bool ShaderProgram::set_matrix(glm::vec3 modelMatrix, const char* variableName) {
	
	uniformLocationID = glGetUniformLocation(this->shaderProgramID, variableName);
	if (uniformLocationID == -1)
	{
		fprintf(stderr, "Variable %s location was not found \n", variableName);
		exit(-1);
	}
	glUniform3fv(uniformLocationID, 1, &modelMatrix[0]);

	return true;
}

bool ShaderProgram::set_uniform_number(int number, const char* variableName) {
	
	uniformLocationID = glGetUniformLocation(this->shaderProgramID, variableName);
	if (uniformLocationID == -1)
	{
		fprintf(stderr, "Variable %s location was not found \n", variableName);
		exit(-1);
	}
	glUniform1i(uniformLocationID, number);

	return true;
}

void ShaderProgram::update()
{
	uniformLocationID = glGetUniformLocation(this->shaderProgramID, "viewMatrix");
	if (uniformLocationID == -1)
	{
		fprintf(stderr, "Variable %s location was not found \n", "viewMatrix");
		exit(-1);
	}
	glUniformMatrix4fv(uniformLocationID, 1, GL_FALSE, &observered_camera->get_view_matrix()[0][0]);

	uniformLocationID = glGetUniformLocation(this->shaderProgramID, "projectionMatrix");
	if (uniformLocationID == -1)
	{
		fprintf(stderr, "Variable %s location was not found \n", "viewMatrix");
		exit(-1);
	}
	glUniformMatrix4fv(uniformLocationID, 1, GL_FALSE, &observered_camera->get_projection_matrix()[0][0]);
}
/*
void ShaderProgram::update(glm::mat4& changed_matrix_value, std::string& changed_matrix_name)
{
	set_matrix(changed_matrix_value, changed_matrix_name.c_str());
}*/

void ShaderProgram::set_observed_camera(Camera* c)
{
	this->observered_camera = c;
	if (!c->search_shader(this)) {
		c->attach_shader(this);
		c->update();
	}
	else
	{
		c->update();
	}
}

bool ShaderProgram::set_view_direction()
{
	return true;
}

bool ShaderProgram::set_eye_position(glm::vec3& eyePosition)
{
	return true;
}

bool ShaderProgram::use_lights()
{
	return false;
}

int ShaderProgram::get_shader_id()
{
	return shaderProgramID;
}
