#include "SceneObjectControllerTest.h"

SceneObjectControllerTest::SceneObjectControllerTest(GLFWwindow* window) : SceneObjectController(window)
{
}

void SceneObjectControllerTest::init_models()
{
	bool variant = false;
	if (variant)
	{
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere1");
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere2");
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere3");
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere4");
	}
	else
	{
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere1");
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::LAMBERT, "sphere2");
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::BLINN, "sphere3");
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::CONSTANT, "sphere4");
	}
	add_point_light(glm::vec3(0, 0, -10), 1, 0, 0, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 1, 1));

}

void SceneObjectControllerTest::static_transformations()
{
	auto sphere1 = drawable_objects[objectKeyMapper["sphere1"]]->transformation;
	sphere1->static_translate(glm::vec3(0,2,-10));
	auto sphere2 = drawable_objects[objectKeyMapper["sphere2"]]->transformation;
	sphere2->static_translate(glm::vec3(2, 0, -10));
	auto sphere3 = drawable_objects[objectKeyMapper["sphere3"]]->transformation;
	sphere3->static_translate(glm::vec3(0, -2, -10));
	auto sphere4 = drawable_objects[objectKeyMapper["sphere4"]]->transformation;
	sphere4->static_translate(glm::vec3(-2, 0, -10));
}

void SceneObjectControllerTest::dynamic_transformations()
{


	for (auto const& [key, value] : drawable_objects)
	{
		value->transformation->compute_trans_matrix();
	}
}
