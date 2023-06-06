#pragma once
#include "SceneObjectController.h"
#include <random>

class SceneControllerTest3 : public SceneObjectController
{
public:
	SceneControllerTest3(GLFWwindow* window);
	virtual void init_models() override;
	virtual void static_transformations() override;
	virtual void dynamic_transformations() override;

};