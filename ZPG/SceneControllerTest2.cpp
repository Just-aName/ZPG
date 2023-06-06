#include "SceneControllerTest2.h"

SceneControllerTest2::SceneControllerTest2(GLFWwindow* window) : SceneObjectController(window, glm::vec3(0, 0, 0), glm::vec3(0, 0, -10))
{
}

void SceneControllerTest2::init_models()
{
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere1");
}

void SceneControllerTest2::static_transformations()
{
	glm::mat4 M4 = glm::mat4(1.0f);

	M4 = glm::translate(M4, glm::vec3(0, 0, -5));

	Transformation* trans4 = new Transformation(M4);

	if (drawable_objects.contains(objectKeyMapper["sphere1"]))
		drawable_objects[objectKeyMapper["sphere1"]]->set_trans_matrix(trans4);
}

void SceneControllerTest2::dynamic_transformations()
{

}