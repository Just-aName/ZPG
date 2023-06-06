#pragma once
#include "SceneObjectController.h"
#include "SceneObjectControllerForest.h"
#include "SceneControllerTest3.h"

class Scene
{
protected:
	static Scene* instance;
	SceneObjectController* sceneObjectController;
	GLFWwindow* window;
	bool mousePress = false;
	Scene(int winWidth = 640, int winHeight = 480);

public:
	static Scene* getInstance();
	static void destroy();

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
    static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	
	static void getWindowSize(int* width, int* height);
	static void main_loop();
};

