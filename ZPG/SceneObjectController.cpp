#pragma once
#include "SceneObjectController.h"
#include <cmath>




SceneObjectController::SceneObjectController(GLFWwindow* window)
{
	this->window = window;
	drawable_objects = std::map<int, DrawableObject*>();
	objectKeyMapper = std::map<std::string, int>();
	camera = new Camera(glm::mat4(1.0f), glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f), glm::vec3(0, 0, 0));
	lights = std::vector<shared_ptr<Light>>();
	textureManager = make_shared<TextureManager>();
	skyBox = shared_ptr<DrawableObjectSkyBox>(nullptr);
}

SceneObjectController::SceneObjectController(GLFWwindow* window, glm::vec3 cameraPosition)
{
	this->window = window;
	drawable_objects = std::map<int, DrawableObject*>();
	objectKeyMapper = std::map<std::string, int>();
	camera = new Camera(glm::mat4(1.0f), glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f), cameraPosition);
	lights = std::vector<shared_ptr<Light>>();
	textureManager = make_shared<TextureManager>();
	skyBox = shared_ptr<DrawableObjectSkyBox>(nullptr);
}


SceneObjectController::~SceneObjectController()
{
	for (auto const& [key, value] : drawable_objects)
		delete value;
	if (camera != nullptr)
		delete camera;
	if (window != nullptr)
		window = nullptr;
}

Camera& SceneObjectController::get_camera() const
{
	return *camera;
}

void SceneObjectController::add_drawable_object(const float* data, int size, SHADERTYPE shaderType, const std::string& key, const std::string& texture)
{
	Model* model = nullptr;
	ShaderProgram* shader = nullptr;
	bool cubemap = false;
	switch (shaderType)
	{
	case CONSTANT:
		shader = new ConstantShaderProgram();
		model = new Model(data, size);
		break;
	case LAMBERT:
		shader = new LambertShaderProgram();
		model = new Model(data, size);
		break;
	case PHONG:
		shader = new PhongShaderProgram();
		model = new Model(data, size);
		break;
	case BLINN:
		shader = new BlinnShaderProgram();
		model = new Model(data, size);
		break;
	case CONSTANT_TEXTURES:
		shader = new ConstantShaderProgramTexture();
		model = new ModelWithTexture(data, size);
		break;
	case PHONG_TEXTURES:
		shader = new PhongShaderProgramTexture();
		model = new ModelWithTexture(data, size);
		break;
	case CONSTANT_PLAIN:
		shader = new ConstantShaderProgramPlainModel();
		model = new ModelPlain(data, size);
		cubemap = true;
		break;
	default:
		std::cerr << "Invalid shaderType" << std::endl;
		exit(-1);
		break;
	}

	Transformation* transform = new Transformation();
	lastObjectId++;
	objectKeyMapper.insert_or_assign(key, lastObjectId);
	if (texture.empty())
		drawable_objects.insert_or_assign(lastObjectId, new DrawableObject(model, shader, transform, lastObjectId));
	else
	{
		if(cubemap)
			drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectTexture(model, shader, transform, lastObjectId, textureManager->getCubemap(texture)->getLayerId()));
		else
			drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectTexture(model, shader, transform, lastObjectId, textureManager->getTexture(texture)->getLayerId()));
	}

}

void SceneObjectController::add_drawable_object_assimp(const std::string& key, const std::string& model, const std::string& texture, const std::string& normals)
{
	lastObjectId += 1;
	if (normals.empty())
	{
		objectKeyMapper.insert_or_assign(key, lastObjectId);
		drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectTexture(new ModelAssimp(model), new PhongShaderProgramTexture(), new Transformation(), lastObjectId, textureManager->getTexture(texture)->getLayerId()));
	}
	else
	{
		objectKeyMapper.insert_or_assign(key, lastObjectId);
		drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectAssimp(new ModelAssimp(model), new PhongShaderProgramAssimp(), new Transformation(), lastObjectId, textureManager->getTexture(texture)->getLayerId(), textureManager->getTexture(normals)->getLayerId()));
	}
}

void SceneObjectController::add_point_light(glm::vec3 position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
{
	lights.push_back(
		make_shared<PointLight>(
			position,
			constantAttenuation,
			linearAttenuation,
			quadraticAttenuation,
			ambient,
			diffuse,
			specular,
			color
			));
}

void SceneObjectController::add_direction_light(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
{
	lights.push_back(
		make_shared<DirectionLight>(
			direction,
			ambient,
			diffuse,
			specular,
			color
			));
}

void SceneObjectController::add_spot_light(glm::vec3 position, glm::vec3 direction, float spotCutOff, float spotOuterCutOff, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
{
	lights.push_back(
		make_shared<Spotlight>(
			position,
			direction,
			spotCutOff,
			spotOuterCutOff,
			constantAttenuation,
			linearAttenuation,
			quadraticAttenuation,
			ambient,
			diffuse,
			specular,
			color
			));
}

void SceneObjectController::init_vao_vbo_shader() 
{
	if (skyBox != nullptr)
	{
		this->skyBox->create_vao_vbo();
		this->skyBox->set_shader();
	}
	for (auto const& [key, value] : drawable_objects)
	{
		if (!value->create_vao_vbo())
		{
			std::cout << "vao/vbo init error" << std::endl;
			return;
		}
		value->set_shader(); // Setting shader program and compiling him.
		//Set lights
		if (!value->use_lights())
			continue;
		int index = 0;
		for (auto const& light : lights)
		{
			index = light->addLight(index, index, value->shader->get_shader_id());
		}
		value->shader->set_uniform_number(batteryOn, "battery");
	}
}

void SceneObjectController::init_models()
{
	float pos = 0.0f;
	const float TRIA1[18] = {
		-0.1f + pos, -0.9f + pos, 0.0f + pos, 0.5f, 0.0f, 0.5f,				// b
		-0.1f + pos, +0.8f + pos, 0.0f + pos, 0.5f, 0.5f, 0.0f,				// c
		-0.9f + pos, -0.9f + pos, 0.0f + pos, 0.0f, 0.5f, 1.0f				// a 
	};
	const float TRIA2[18] = {
		+0.1f + pos, -0.9f + pos, 0.0f + pos, 0.0f, 0.0f, 1.0f,				// a
		+0.1f + pos, +0.8f + pos, 0.0f + pos, 1.0f, 0.0f, 0.0f,				// c
		0.9f + pos, -0.9f + pos, 0.0f + pos, 0.0f, 1.0f, 0.0f				// b
	};

	const float square[36] = {
		1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	const float triangle[48] = {
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,

		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f
	};

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

	skyBox.reset( new DrawableObjectSkyBox(new ModelPlain(skyboxModel, sizeof(skyboxModel) / sizeof(skyboxModel[0])), new ConstantShaderProgramSkyBox(), new Transformation(), -1, textureManager->getCubemap("skybox_cubemap")->getLayerId()));


	add_drawable_object(square, sizeof(square) / sizeof(square[0]), SHADERTYPE::CONSTANT, "square1");
	//Scene::add_drawable_object(TRIA1, sizeof(TRIA1) / sizeof(TRIA1[0]), SHADERTYPE::CONSTANT, "tria1");
	//Scene::add_drawable_object(TRIA2, sizeof(TRIA2) / sizeof(TRIA2[0]), SHADERTYPE::CONSTANT, "tria2");
	add_drawable_object(square, sizeof(square) / sizeof(square[0]), SHADERTYPE::CONSTANT, "square2");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::LAMBERT, "sphere1");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere2");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere3");
	add_drawable_object(sphere, sizeof(sphere) / sizeof(sphere[0]), SHADERTYPE::PHONG, "sphere4");
	add_drawable_object(plain, sizeof(plain) / sizeof(plain[0]), SHADERTYPE::PHONG, "plain1");
	add_drawable_object(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]), SHADERTYPE::PHONG, "suziFlat1");
	add_drawable_object(suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]), SHADERTYPE::PHONG, "suziSmooth1");
	add_drawable_object(triangle, sizeof(triangle) / sizeof(triangle[0]), SHADERTYPE::PHONG_TEXTURES, "plainText1", "wooden_fence");
	add_drawable_object(triangle, sizeof(triangle) / sizeof(triangle[0]), SHADERTYPE::CONSTANT_TEXTURES, "plainText2", "grass");
	add_drawable_object(skyboxModel, sizeof(skyboxModel) / sizeof(skyboxModel[0]), SHADERTYPE::CONSTANT_PLAIN, "skyboxPlain", "skybox_cubemap");
	
	add_drawable_object_assimp("house1", "ModelObjects/model.obj", "test");
	add_drawable_object_assimp("box1", "ModelObjects/Box/model.obj", "box", "boxNormals");
	add_drawable_object_assimp("zombie1", "ModelObjects/zombie.obj", "zombie");
	/*
	lastObjectId += 1;
	objectKeyMapper.insert_or_assign("house1", lastObjectId);
	drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectTexture(new ModelAssimp("ModelObjects/model.obj"), new PhongShaderProgramTexture(), new Transformation(), lastObjectId, textureManager->getTexture("test")->getLayerId()));

	lastObjectId += 1;
	objectKeyMapper.insert_or_assign("box1", lastObjectId);
	drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectAssimp(new ModelAssimp("ModelObjects/Box/model.obj"), new PhongShaderProgramAssimp(), new Transformation(), lastObjectId, textureManager->getTexture("box")->getLayerId(), textureManager->getTexture("boxNormals")->getLayerId()));

	lastObjectId += 1;
	objectKeyMapper.insert_or_assign("zombie1", lastObjectId);
	drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectTexture(new ModelAssimp("ModelObjects/zombie.obj"), new PhongShaderProgramTexture(), new Transformation(), lastObjectId, textureManager->getTexture("zombie")->getLayerId()));
	*/

	add_direction_light(glm::vec3(0, -1, 0), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f));
	add_point_light(glm::vec3(0, 0, -10), 1, 0, 0, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 1, 1));
	add_spot_light(glm::vec3(10, 0, 10), glm::vec3(0, -1, 0), 12.5f, 17.5f, 1, 0, 0, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0));
	add_spot_light(glm::vec3(12, 0, 12), glm::vec3(0, -1, 0), 12.5f, 17.5f, 1, 0, 0, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 0, 0));
}

void SceneObjectController::init_textures()
{
	textureManager->add("skybox_cubemap", make_shared<Cubemap>(
		"posx.jpg",
		"negx.jpg",
		"posy.jpg",
		"negy.jpg",
		"posz.jpg",
		"negz.jpg"
		));

	textureManager->add("wooden_fence", make_shared<Texture>("wooden_fence.png"));
	textureManager->add("grass", make_shared<Texture>("grass.png"));
	textureManager->add("zombie", make_shared<Texture>("ModelObjects/zombie.png"));
	textureManager->add("tree", make_shared<Texture>("ModelObjects/tree.png"));
	textureManager->add("test", make_shared<Texture>("ModelObjects/test.png"));
	textureManager->add("box", make_shared<Texture>("ModelObjects/Box/albedo.png"));
	textureManager->add("boxNormals", make_shared<Texture>("ModelObjects/Box/normalmap.png"));
	textureManager->add("teren", make_shared<Texture>("negy.jpg"));
	textureManager->add("street", make_shared<Texture>("ModelObjects/street.png"));

	textureManager->load();
}

void SceneObjectController::dynamic_transformations()
{
	if (angle >= 360)
		angle = 0;
	angle++;

	size += sizeChange;
	
	glm::mat4 M0 = glm::mat4(1.0f);
	glm::mat4 M1 = glm::mat4(1.0f);
	glm::mat4 M2 = glm::mat4(1.0f);
	glm::mat4 M3 = glm::mat4(1.0f);
	glm::mat4 M4 = glm::mat4(1.0f);
	glm::mat4 M5 = glm::mat4(1.0f);
	glm::mat4 M6 = glm::mat4(1.0f);
	glm::mat4 M7 = glm::mat4(1.0f);
	glm::mat4 M8 = glm::mat4(1.0f);
	glm::mat4 M9 = glm::mat4(1.0f);
	glm::mat4 M10 = glm::mat4(1.0f);
	glm::mat4 M11 = glm::mat4(1.0f);
	glm::mat4 M12 = glm::mat4(1.0f);
	glm::mat4 M13 = glm::mat4(1.0f);



	M0 = glm::translate(M0, glm::vec3(0, -5, 0));
	M0 = glm::rotate(M0, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	M0 = glm::translate(M0, glm::vec3(5, 0, 0));

	M3 = glm::scale(glm::vec3(0.5, 1, 0.5));
	M3 = M0 * M3;
	M3 = glm::rotate(M3, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	M3 = glm::translate(M3, glm::vec3(5, 0, 0));
	M3 = glm::rotate(M3, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));




	M1 = glm::translate(M1, glm::vec3(1, 1, 5));
	M1 = glm::rotate(M1, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	M1 = glm::translate(M1, glm::vec3(-1, -1, 5));

	// M2 rotace kolem osy y
	M2 = glm::translate(M2, glm::vec3(15, -10, 0));
	//M2 = glm::rotate(M2, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));



	//rotate sphere group around z axe
	M4 = glm::translate(M4, glm::vec3(0, 0, -10));
	M4 = glm::rotate(M4, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	M4 = glm::translate(M4, glm::vec3(0, 2, 0));
	//M4 = glm::rotate(M4, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	M5 = glm::translate(M5, glm::vec3(0, 0, -10));
	M5 = glm::rotate(M5, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	M5 = glm::translate(M5, glm::vec3(2, 0, 0));
	//M5 = glm::rotate(M5, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));


	M6 = glm::translate(M6, glm::vec3(0, 0, -15));
	//M6 = glm::rotate(M6, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	//M6 = glm::translate(M6, glm::vec3(0, -2, 0));
	//M6 = glm::rotate(M6, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));

	M7 = glm::translate(M7, glm::vec3(0, 0, -10));
	M7 = glm::rotate(M7, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	M7 = glm::translate(M7, glm::vec3(-2, 0, 0));

	M8 = glm::scale(M8, glm::vec3(400, 1, 400));
	M8 = glm::translate(M8, glm::vec3(0, -10, 0));

	M9 = glm::translate(M9, glm::vec3(5, 0, -2));
	M9 = glm::rotate(M9, glm::radians((float)-90), glm::vec3(0.0f, 1.0f, 0.0f));

	M10 = glm::translate(M10, glm::vec3(5, 0, 2));
	M10 = glm::rotate(M10, glm::radians((float)-90), glm::vec3(0.0f, 1.0f, 0.0f));

	M11 = glm::translate(M11, glm::vec3(0, 0, 15));
	M11 = glm::scale(M11, glm::vec3(-5, 5, 1));
	M11 = glm::rotate(M11, glm::radians((float)-180), glm::vec3(0.0f, 1.0f, 0.0f));
	M12 = glm::translate(M12, glm::vec3(0, 0, 10));
	M12 = glm::translate(M12, glm::vec3(3, 0, 0));
	
	M13 = glm::translate(M13, glm::vec3(-5, 0, 0));

	Transformation* trans0 = new Transformation(M0);
	Transformation* trans1 = new Transformation(M1);
	Transformation* trans2 = new Transformation(M2);
	Transformation* trans3 = new Transformation(M3);
	Transformation* trans4 = new Transformation(M4);
	Transformation* trans5 = new Transformation(M5);
	Transformation* trans6 = new Transformation(M6);
	Transformation* trans7 = new Transformation(M7);
	Transformation* trans8 = new Transformation(M8);
	Transformation* trans9 = new Transformation(M9);
	Transformation* trans10 = new Transformation(M10);
	Transformation* trans11 = new Transformation(M11);
	Transformation* trans12 = new Transformation(M12);
	Transformation* trans13 = new Transformation(M13);
	
	glm::mat4 M = glm::mat4(1.0f);
	
	glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));
	glm::mat4x3 B = glm::mat4x3(glm::vec3(-1, 0, 0),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, -1),
		glm::vec3(1, 0, 0));

	glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
	glm::vec3 p = parameters * A * glm::transpose(B);
	M = glm::translate(glm::mat4(1.0f), p);

	if (t >= 1.0f || t <= 0.0f) delta *= -1;
	t += delta;
	
	parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
	glm::vec3 pOld = parameters * A * glm::transpose(B);

	auto deltaX = pOld.x - p.x;
	auto deltaY = pOld.z - p.z;
	auto degree = std::atan2f(deltaY, deltaX);
	auto angle = degree * 180 / 3.14;
	if (angle < 0)
	{
		angle = 360 + angle;
	}
	M = glm::rotate(M, glm::radians((float)angle), glm::vec3(0.0f, 1.0f, 0.0f));
	/*
	glm::vec3 A = glm::vec3(0, 0, 0);
	glm::vec3 point = A + glm::vec3(-10, 0, 0) * t;
	M = glm::translate(glm::mat4(1.0f), point);

	if (t >= 1.0f || t <= 0.0f) delta *= -1;
	t += delta;

	glm::vec3 point2 = A + glm::vec3(-10, 0, 0) * t;
	auto deltaX = point.x - point2.x;
	auto deltaY = point.z - point2.z;
	auto degree = std::atan2f(deltaY, deltaX);
	auto angle = degree * 180 / 3.14;
	if (angle < 0)
	{
		angle = 360 + angle;
	}
	M = glm::rotate(M, glm::radians((float)angle - 90), glm::vec3(0.0f, 1.0f, 0.0f));
	*/
	Transformation* trs = new Transformation(M);


	if (drawable_objects.contains(objectKeyMapper["square1"]))
		drawable_objects[objectKeyMapper["square1"]]->set_trans_matrix(trans0);
	if (drawable_objects.contains(objectKeyMapper["tria1"]))
		drawable_objects[objectKeyMapper["tria1"]]->set_trans_matrix(trans1);
	if (drawable_objects.contains(objectKeyMapper["tria2"]))
		drawable_objects[objectKeyMapper["tria2"]]->set_trans_matrix(trans2);
	if (drawable_objects.contains(objectKeyMapper["square2"]))
		drawable_objects[objectKeyMapper["square2"]]->set_trans_matrix(trans3);
	if (drawable_objects.contains(objectKeyMapper["sphere1"]))
		drawable_objects[objectKeyMapper["sphere1"]]->set_trans_matrix(trans4);
	if (drawable_objects.contains(objectKeyMapper["sphere2"]))
		drawable_objects[objectKeyMapper["sphere2"]]->set_trans_matrix(trans5);
	if (drawable_objects.contains(objectKeyMapper["sphere3"]))
		drawable_objects[objectKeyMapper["sphere3"]]->set_trans_matrix(trans6);
	if (drawable_objects.contains(objectKeyMapper["sphere4"]))
		drawable_objects[objectKeyMapper["sphere4"]]->set_trans_matrix(trans7);
	if (drawable_objects.contains(objectKeyMapper["plain1"]))
		drawable_objects[objectKeyMapper["plain1"]]->set_trans_matrix(trans8);
	if (drawable_objects.contains(objectKeyMapper["suziFlat1"]))
		drawable_objects[objectKeyMapper["suziFlat1"]]->set_trans_matrix(trans9);
	if (drawable_objects.contains(objectKeyMapper["suziSmooth1"]))
		drawable_objects[objectKeyMapper["suziSmooth1"]]->set_trans_matrix(trans10);
	if (drawable_objects.contains(objectKeyMapper["plainText1"]))
		drawable_objects[objectKeyMapper["plainText1"]]->set_trans_matrix(trans11);
	if (drawable_objects.contains(objectKeyMapper["plainText2"]))
		drawable_objects[objectKeyMapper["plainText2"]]->set_trans_matrix(trans12);
	if (drawable_objects.contains(objectKeyMapper["skyboxPlain"]))
		drawable_objects[objectKeyMapper["skyboxPlain"]]->set_trans_matrix(trans13);
	if (drawable_objects.contains(objectKeyMapper["house1"]))
		drawable_objects[objectKeyMapper["house1"]]->set_trans_matrix(trans2);
	if (drawable_objects.contains(objectKeyMapper["box1"]))
		drawable_objects[objectKeyMapper["box1"]]->set_trans_matrix(trans1);
	if (drawable_objects.contains(objectKeyMapper["zombie1"]))
		drawable_objects[objectKeyMapper["zombie1"]]->set_trans_matrix(trs);
}

void SceneObjectController::static_transformations()
{

}

void SceneObjectController::add_or_remove_object()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	GLbyte color[4];
	GLfloat depth;
	GLuint index; // identifikace tìlesa
	int x = (width / 2);
	int y = (height / 2);
	int newy = height - y;
	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

	if (index != objectKeyMapper["plain1"] && index != objectKeyMapper["teren"] && drawable_objects.contains(index) && false)
	{
		drawable_objects.erase(index);
	}
	else
	{
		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::vec4 viewPort = glm::vec4(0, 0, width, height);
		//Map the specified window coordinates (win.x, win.y, win.z) into object coordinates
		glm::vec3 pos = glm::unProject(screenX, camera->get_view_matrix(), camera->get_projection_matrix(), viewPort);

		lastObjectId += 1;
		objectKeyMapper.insert_or_assign("zombieClick", lastObjectId);
		drawable_objects.insert_or_assign(lastObjectId, new DrawableObjectTexture(new ModelAssimp("ModelObjects/zombie.obj"), new PhongShaderProgramTexture(), new Transformation(), lastObjectId, textureManager->getTexture("zombie")->getLayerId()));
		
		init_vao_vbo_shader();

		drawable_objects[objectKeyMapper["zombieClick"]]->transformation->dynamic_translate(pos);
		drawable_objects[objectKeyMapper["zombieClick"]]->transformation->compute_trans_matrix();

		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
	}
}

void SceneObjectController::draw_objects()
{
	if (skyBox != nullptr)
	{
		this->skyBox->set_shader(nullptr);
		this->skyBox->draw(camera);
	}
	for (auto const& [key, value] : drawable_objects) {
		value->set_shader(nullptr);
		value->draw(camera);
	}
}
