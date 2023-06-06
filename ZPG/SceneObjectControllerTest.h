#pragma once
#include "SceneObjectController.h"
class SceneObjectControllerTest :
    public SceneObjectController
{
public:
	SceneObjectControllerTest(GLFWwindow* window);
	virtual void init_models() override;
	virtual void static_transformations() override;
	virtual void dynamic_transformations() override;
};

