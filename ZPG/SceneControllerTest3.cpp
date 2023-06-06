#include "SceneControllerTest3.h"

SceneControllerTest3::SceneControllerTest3(GLFWwindow* window) : SceneObjectController(window, glm::vec3(0, 5, 5))
{
}

void SceneControllerTest3::init_models()
{/*
	for (int i = 0; i < 20; i++)
	{
		add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere" + std::to_string(i));
	}
	for (int i = 0; i < 30; i++)
	{
		add_drawable_object(tree, sizeof(tree) / sizeof(tree[0]), SHADERTYPE::LAMBERT, "tree" + std::to_string(i));
	}
	for (int i = 0; i < 30; i++)
	{
		add_drawable_object(bushes, sizeof(bushes) / sizeof(bushes[0]), SHADERTYPE::CONSTANT, "bushes" + std::to_string(i));
	}
	for (int i = 0; i < 10; i++)
	{
		add_drawable_object(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]), SHADERTYPE::CONSTANT, "suziFlat" + std::to_string(i));
	}
	for (int i = 0; i < 10; i++)
	{
		add_drawable_object(suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]), SHADERTYPE::CONSTANT, "suziSmooth" + std::to_string(i));
	}
	for (int i = 0; i < 10; i++)
	{
		add_drawable_object(gift, sizeof(gift) / sizeof(gift[0]), SHADERTYPE::CONSTANT, "gift" + std::to_string(i));
	}

	add_drawable_object(plain, sizeof(plain) / sizeof(plain[0]), SHADERTYPE::BLINN, "plain0");*/
}

void SceneControllerTest3::static_transformations()
{/*
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 30); // distribution in range [1, 30]
	std::uniform_int_distribution<std::mt19937::result_type> dist8(1, 359); // distribution in range [1, 359]

	std::cout << dist6(rng) << std::endl;
	std::string str;
	str = "tree";
	for (int i = 0; i < 20; i++)
	{
		glm::mat4 M0 = glm::mat4(1.0f);
		M0 = glm::translate(M0, glm::vec3(dist6(rng), 0, dist6(rng)));
		Transformation* trans = new Transformation(M0);
		if (drawable_objects.contains(objectKeyMapper["tree" + std::to_string(i)]))
			drawable_objects[objectKeyMapper["tree" + std::to_string(i)]]->set_trans_matrix(trans);
	}
	for (int i = 0; i < 30; i++)
	{
		glm::mat4 M0 = glm::mat4(1.0f);
		M0 = glm::translate(M0, glm::vec3(dist6(rng), 15, dist6(rng)));
		Transformation* trans = new Transformation(M0);
		if (drawable_objects.contains(objectKeyMapper["sphere" + std::to_string(i)]))
			drawable_objects[objectKeyMapper["sphere" + std::to_string(i)]]->set_trans_matrix(trans);
	}
	for (int i = 0; i < 30; i++)
	{
		glm::mat4 M0 = glm::mat4(1.0f);
		M0 = glm::translate(M0, glm::vec3(dist6(rng), 0, dist6(rng)));
		Transformation* trans = new Transformation(M0);
		if (drawable_objects.contains(objectKeyMapper["bushes" + std::to_string(i)]))
			drawable_objects[objectKeyMapper["bushes" + std::to_string(i)]]->set_trans_matrix(trans);
	}
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 M0 = glm::mat4(1.0f);
		M0 = glm::translate(M0, glm::vec3(dist6(rng), 3, dist6(rng)));
		M0 = glm::rotate(M0, glm::radians((float)dist8(rng)), glm::vec3(0.0f, 1.0f, 0.0f));
		Transformation* trans = new Transformation(M0);
		if (drawable_objects.contains(objectKeyMapper["suziFlat" + std::to_string(i)]))
			drawable_objects[objectKeyMapper["suziFlat" + std::to_string(i)]]->set_trans_matrix(trans);
	}
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 M0 = glm::mat4(1.0f);
		M0 = glm::translate(M0, glm::vec3(dist6(rng), 3, dist6(rng)));
		M0 = glm::rotate(M0, glm::radians((float)dist8(rng)), glm::vec3(0.0f, 1.0f, 0.0f));
		Transformation* trans = new Transformation(M0);
		if (drawable_objects.contains(objectKeyMapper["suziSmooth" + std::to_string(i)]))
			drawable_objects[objectKeyMapper["suziSmooth" + std::to_string(i)]]->set_trans_matrix(trans);
	}
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 M0 = glm::mat4(1.0f);
		M0 = glm::translate(M0, glm::vec3(dist6(rng), 0, dist6(rng)));
		Transformation* trans = new Transformation(M0);
		if (drawable_objects.contains(objectKeyMapper["gift" + std::to_string(i)]))
			drawable_objects[objectKeyMapper["gift" + std::to_string(i)]]->set_trans_matrix(trans);
	}
	
	glm::mat4 M0 = glm::mat4(1.0f);
	M0 = glm::translate(M0, glm::vec3(15, 0, 15));
	M0 = glm::scale(M0, glm::vec3(30, 1, 30));
	Transformation* trans = new Transformation(M0);
	if (drawable_objects.contains(objectKeyMapper["plain0"]))
		drawable_objects[objectKeyMapper["plain0"]]->set_trans_matrix(trans);*/
}

void SceneControllerTest3::dynamic_transformations()
{

}