#pragma once
#include "SceneObjectControllerForest.h"

SceneObjectControllerForest::SceneObjectControllerForest(GLFWwindow* window) : SceneObjectControllerTest(window)
{
}

void SceneObjectControllerForest::init_models()
{
	float skyboxModel[] = {
-1.000, -1.000, 1.000,
-1.000, 1.000, -1.000,
-1.000, -1.000, -1.000,
-1.000, 1.000, 1.000,
1.000, 1.000, -1.000,
-1.000, 1.000, -1.000,
1.000, 1.000, 1.000,
1.000, -1.000, -1.000,
1.000, 1.000, -1.000,
1.000, -1.000, 1.000,
-1.000, -1.000, -1.000,
1.000, -1.000, -1.000,
1.000, 1.000, -1.000,
-1.000, -1.000, -1.000,
-1.000, 1.000, -1.000,
-1.000, 1.000, 1.000,
1.000, -1.000, 1.000,
1.000, 1.000, 1.000,
-1.000, -1.000, 1.000,
-1.000, 1.000, 1.000,
-1.000, 1.000, -1.000,
-1.000, 1.000, 1.000,
1.000, 1.000, 1.000,
1.000, 1.000, -1.000,
1.000, 1.000, 1.000,
1.000, -1.000, 1.000,
1.000, -1.000, -1.000,
1.000, -1.000, 1.000,
-1.000, -1.000, 1.000,
-1.000, -1.000, -1.000,
1.000, 1.000, -1.000,
1.000, -1.000, -1.000,
-1.000, -1.000, -1.000,
-1.000, 1.000, 1.000,
-1.000, -1.000, 1.000,
1.000, -1.000, 1.000,
	};

	skyBox.reset(new DrawableObjectSkyBox(new ModelPlain(skyboxModel, sizeof(skyboxModel) / sizeof(skyboxModel[0])), new ConstantShaderProgramSkyBox(), new Transformation(), -1, textureManager->getCubemap("skybox_cubemap")->getLayerId()));

	
	for (int i = 0; i < 10; i++)
	{
		add_drawable_object_assimp("test" + std::to_string(i), "ModelObjects/model.obj", "test");
	}
	for (int i = 0; i < 50; i++)
	{
		add_drawable_object_assimp("tree" + std::to_string(i), "ModelObjects/tree.obj", "tree");
	}

	add_drawable_object_assimp("zombie1", "ModelObjects/zombie.obj", "zombie");

	add_drawable_object_assimp("teren", "ModelObjects/teren.obj", "teren");

	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere1");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere2");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere3");
	add_drawable_object_assimp("box1", "ModelObjects/Box/model.obj", "box", "boxNormals");
	//add_drawable_object(plain, sizeof(plain) / sizeof(plain[0]), SHADERTYPE::PHONG, "plain1");

	add_direction_light(glm::vec3(0, -1, 0), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.8f, 0.8f, 0.8f));
	add_point_light(glm::vec3(20, 10, 20), 1.0f, 2.0f, 3.0f, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 1, 0));
	add_spot_light(glm::vec3(64, 12, -50), glm::vec3(0, -1, 0), 12.5f, 17.5f, 2.0f, 1.0f, 1.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 0, 0));
	add_spot_light(glm::vec3(68, 12, -50), glm::vec3(0, -1, 0), 12.5f, 17.5f, 2.0f, 1.0f, 1.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1));

}

void SceneObjectControllerForest::static_transformations()
{
	auto teren = drawable_objects[objectKeyMapper["teren"]]->transformation;
	teren->static_scale(glm::vec3(10, 1, 10));

	auto zombie1 = drawable_objects[objectKeyMapper["zombie1"]]->transformation;
	zombie1->static_translate(glm::vec3(0, 0, -50));
	zombie1->static_rotate(-90, glm::vec3(0, 1, 0));

	auto sphere1 = drawable_objects[objectKeyMapper["sphere1"]]->transformation;
	sphere1->static_translate(glm::vec3(62, 6, -50));

	auto sphere2 = drawable_objects[objectKeyMapper["sphere2"]]->transformation;
	sphere2->static_translate(glm::vec3(66, 6, -50));

	auto sphere3 = drawable_objects[objectKeyMapper["sphere3"]]->transformation;
	sphere3->static_translate(glm::vec3(70, 6, -50));
	/*
	auto plain1 = drawable_objects[objectKeyMapper["plain1"]]->transformation;
	plain1->static_translate(glm::vec3(66, 1, -50));
	plain1->static_scale(glm::vec3(10, 1, 10));
	*/

	auto box1 = drawable_objects[objectKeyMapper["box1"]]->transformation;
	box1->static_translate(glm::vec3(55, 1, -50));
	
	for (int i = 0; i < 10; i++)
	{
		if (i < 5)
		{
			auto test = drawable_objects[objectKeyMapper["test" + std::to_string(i)]]->transformation;
			test->static_translate(glm::vec3(i * 15, 0, -20));
		}
		else
		{
			auto test = drawable_objects[objectKeyMapper["test" + std::to_string(i)]]->transformation;
			test->static_translate(glm::vec3((i-5)  * 15, 0, -80));
		}
	}

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 50); // distribution in range [1, 30]
	for (int i = 0; i < 50; i++)
	{
		auto tree = drawable_objects[objectKeyMapper["tree" + std::to_string(i)]]->transformation;
		tree->static_translate(glm::vec3(dist6(rng), 0, dist6(rng)));
		tree->static_scale(glm::vec3(0.3, 0.3, 0.3));
	}

}

void SceneObjectControllerForest::dynamic_transformations()
{
	glm::vec3 A = glm::vec3(0, 0, -50);
	glm::vec3 point = A + glm::vec3(0, 0, 50) * t;
	auto zombie1 = drawable_objects[objectKeyMapper["zombie1"]]->transformation;
	zombie1->dynamic_clear();
	zombie1->dynamic_translate(point);
	if (delta > 0)
		zombie1->dynamic_rotate(-180, glm::vec3(0, 1, 0));

	if (t >= 1.0f || t <= 0.0f)
	{
		delta *= -1;
	}
	t += delta;

	for (auto const& [key, value] : drawable_objects)
	{
		value->transformation->compute_trans_matrix();
	}
}
