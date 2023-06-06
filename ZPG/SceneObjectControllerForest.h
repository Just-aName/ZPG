#pragma once
#include "SceneObjectControllerTest.h"
#include <random>

class SceneObjectControllerForest :
    public SceneObjectControllerTest
{
	float t = 0.5f;
	float delta = 0.005;
public:
	SceneObjectControllerForest(GLFWwindow* window);
	virtual void init_models() override;
	virtual void static_transformations() override;
	virtual void dynamic_transformations() override;
};

