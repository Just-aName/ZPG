#include "SceneControllerTest1.h"

SceneControllerTest1::SceneControllerTest1(GLFWwindow* window) : SceneObjectController(window, glm::vec3(0,0,0), glm::vec3(0,0,-10))
{
}

void SceneControllerTest1::init_models()
{
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere1");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere2");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere3");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere4");
}

void SceneControllerTest1::dynamic_transformations()
{
	glm::mat4 M4 = glm::mat4(1.0f);
	glm::mat4 M5 = glm::mat4(1.0f);
	glm::mat4 M6 = glm::mat4(1.0f);
	glm::mat4 M7 = glm::mat4(1.0f);

	M4 = glm::translate(M4, glm::vec3(0, 0, -10));
	M4 = glm::translate(M4, glm::vec3(0, 2, 0));
	
	M5 = glm::translate(M5, glm::vec3(0, 0, -10));
	M5 = glm::translate(M5, glm::vec3(2, 0, 0));
	
	M6 = glm::translate(M6, glm::vec3(0, 0, -10));
	M6 = glm::translate(M6, glm::vec3(0, -2, 0));
	
	M7 = glm::translate(M7, glm::vec3(0, 0, -10));
	M7 = glm::translate(M7, glm::vec3(-2, 0, 0));

	Transformation* trans4 = new Transformation(M4);
	Transformation* trans5 = new Transformation(M5);
	Transformation* trans6 = new Transformation(M6);
	Transformation* trans7 = new Transformation(M7);

	if (drawable_objects.contains(objectKeyMapper["sphere1"]))
		drawable_objects[objectKeyMapper["sphere1"]]->set_trans_matrix(trans4);
	if (drawable_objects.contains(objectKeyMapper["sphere2"]))
		drawable_objects[objectKeyMapper["sphere2"]]->set_trans_matrix(trans5);
	if (drawable_objects.contains(objectKeyMapper["sphere3"]))
		drawable_objects[objectKeyMapper["sphere3"]]->set_trans_matrix(trans6);
	if (drawable_objects.contains(objectKeyMapper["sphere4"]))
		drawable_objects[objectKeyMapper["sphere4"]]->set_trans_matrix(trans7);
}

void SceneControllerTest1::static_transformations()
{

}