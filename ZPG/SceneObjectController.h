#pragma once
#include "ShaderTypes.h"
#include "VertexData.h"
#include "Model.h"
#include "Camera.h"
#include "DrawableObjectTexture.h"
#include "DrawableObjectSkyBox.h"
#include "DrawableObjectAssimp.h"
#include "Light.h"
#include "SpotLight.h"
#include "DirectionLight.h"
#include "PointLight.h"

#include "ShaderProgram.h"
#include "PhongShaderProgramAssimp.h"
#include "PhongShaderProgramTexture.h"
#include "ConstantShaderProgramSkyBox.h"
#include "LambertShaderProgram.h"
#include "BlinnShaderProgram.h"
#include "ConstantShaderProgramPlainModel.h"
#include "ModelWithTexture.h"
#include "ModelPlain.h"
#include "ModelAssimp.h"

#include "suzi_flat.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_smooth.h"
#include "bushes.h"
#include "gift.h"
#include "tree.h"
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

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>


class SceneObjectController
{
protected:
	int lastObjectId = 0;
	GLFWwindow* window;
	Camera* camera;
	std::map<int, DrawableObject*> drawable_objects;
	std::map<std::string, int> objectKeyMapper;
	std::vector<shared_ptr<Light>> lights;
	shared_ptr<TextureManager> textureManager;
	shared_ptr<DrawableObjectSkyBox> skyBox;
	int batteryOn =1;

public:
	SceneObjectController(GLFWwindow* window);
	SceneObjectController(GLFWwindow* window, glm::vec3 cameraPosition);
	virtual ~SceneObjectController();

	Camera& get_camera() const;
	void add_drawable_object(const float* data, int size, SHADERTYPE shaderType, const std::string& key, const std::string& texture = std::string());
	void add_drawable_object_assimp(const std::string& key, const std::string& model, const std::string& texture, const std::string& normals = std::string());
	void add_point_light(glm::vec3 position, float constantAttenuation = 1.0f, float linearAttenuation = .0f, float quadraticAttenuation = .0f, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f));
	void add_direction_light(glm::vec3 direction, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f));
	void add_spot_light(glm::vec3 position, glm::vec3 direction, float spotCutOff = 12.5f, float spotOuterCutOff = 17.5f, float constantAttenuation = 1.0f, float linearAttenuation = .0f, float quadraticAttenuation = .0f, glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 color = glm::vec3(1.0f));
	void draw_objects();
	virtual void init_models();
	void init_textures();
	void init_vao_vbo_shader();
	virtual void dynamic_transformations();
	virtual void static_transformations();
	void add_or_remove_object();

private:
	float angle = 1;
	float size = 1;
	float sizeChange = -0.00001f;
	float t = 0.5f;
	float delta = 0.005;

};