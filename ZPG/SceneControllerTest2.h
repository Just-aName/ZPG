#pragma once
#include "SceneObjectController.h"

class SceneControllerTest2 : public SceneObjectController
{
public:
	SceneControllerTest2(GLFWwindow* window);
	virtual void init_models() override;
	virtual void static_transformations() override;
	virtual void dynamic_transformations() override;
};