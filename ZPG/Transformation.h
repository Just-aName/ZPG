#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Transformation
{
	glm::mat4 trans_matrix;
	glm::mat4 dynamic_matrix;
	glm::mat4 static_matrix;

public:
	Transformation(glm::mat4 tr = glm::mat4(1.0f));
	~Transformation();
	const void compute_trans_matrix();
	const glm::mat4& get_matrix() const;

	const glm::mat4& get_static_matrix() const;
	
	const void static_rotate(float angle, const glm::vec3& vector);

	const void static_translate(const glm::vec3& vector);

	const void static_scale(const glm::vec3& vector);

	const void static_bind_to_object(const glm::mat4& parentObjTransMatrix);

	const void static_clear();

	const glm::mat4& get_dynamic_matrix() const;

	const void dynamic_rotate(float angle, const glm::vec3& vector);

	const void dynamic_translate(const glm::vec3& vector);

	const void dynamic_scale(const glm::vec3& vector);

	const void dynamic_bind_to_object(const glm::mat4& parentObjTransMatrix);

	const void dynamic_clear();
};

