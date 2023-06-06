#include "Transformation.h"

Transformation::Transformation(glm::mat4 tr)
{
	this->trans_matrix = tr;
	this->dynamic_matrix = glm::mat4(1.0f);
	this->static_matrix = glm::mat4(1.0f);
}

Transformation::~Transformation()
{
}

const void Transformation::compute_trans_matrix()
{
	this->trans_matrix = static_matrix * dynamic_matrix;
}

const glm::mat4& Transformation::get_matrix() const
{
	return this->trans_matrix;
}

const void Transformation::static_rotate(float angle, const glm::vec3& vector)
{
	static_matrix = glm::rotate(static_matrix, glm::radians(angle), vector);
}

const void Transformation::static_translate(const glm::vec3& vector)
{
	static_matrix = glm::translate(static_matrix, vector);
}

const void Transformation::static_scale(const glm::vec3& vector)
{
	static_matrix = glm::scale(static_matrix, vector);
}

const void Transformation::static_bind_to_object(const glm::mat4& parentObjTransMatrix)
{
	static_matrix = parentObjTransMatrix * static_matrix;
}

const void Transformation::static_clear()
{
	static_matrix = glm::mat4(1.0f);
}

const glm::mat4& Transformation::get_static_matrix() const
{
	return this->static_matrix;
}

const void Transformation::dynamic_rotate(float angle, const glm::vec3& vector)
{
	dynamic_matrix = glm::rotate(dynamic_matrix, glm::radians(angle), vector);
}

const void Transformation::dynamic_translate(const glm::vec3& vector)
{
	dynamic_matrix = glm::translate(dynamic_matrix, vector);
}

const void Transformation::dynamic_scale(const glm::vec3& vector)
{
	dynamic_matrix = glm::scale(dynamic_matrix, vector);
}

const void Transformation::dynamic_bind_to_object(const glm::mat4& parentObjTransMatrix)
{
	dynamic_matrix = parentObjTransMatrix * dynamic_matrix;
}

const void Transformation::dynamic_clear()
{
	dynamic_matrix = glm::mat4(1.0f);
}

const glm::mat4& Transformation::get_dynamic_matrix() const
{
	return this->dynamic_matrix;
}