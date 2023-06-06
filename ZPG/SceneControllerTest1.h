#pragma once
#include "SceneObjectController.h"

class SceneControllerTest1 : public SceneObjectController
{
public:
	SceneControllerTest1(GLFWwindow* window);
	virtual void init_models() override;
	virtual void dynamic_transformations() override;
	virtual void static_transformations() override;
};