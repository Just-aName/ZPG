#include "Scene.h"


Scene* Scene::instance = nullptr;

Scene* Scene::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Scene(640, 480);
	}
	return instance;
}

Scene::Scene(int winWidth, int winHeight)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(winWidth, winHeight, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	//glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
	glViewport(0, 0, width, height);

	// Enable Z-Index
	glEnable(GL_DEPTH_TEST);
	// Enable STENCIL buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	sceneObjectController = new SceneObjectController(window);
	//sceneObjectController = new SceneObjectControllerTest(window);
	//sceneObjectController = new SceneObjectControllerForest(window);
	sceneObjectController->init_textures();
	sceneObjectController->init_models();

}
void Scene::destroy()
{
	if (instance->sceneObjectController != nullptr)
		delete instance->sceneObjectController;
	glfwDestroyWindow(instance->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
void Scene::error_callback(int error, const char* description) { fputs(description, stderr); }

void Scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		instance->sceneObjectController->get_camera().frontMove();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		instance->sceneObjectController->get_camera().rightMove();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		instance->sceneObjectController->get_camera().backMove();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		instance->sceneObjectController->get_camera().leftMove();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		instance->sceneObjectController->get_camera().setMoveSpeed(0.5f);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		instance->sceneObjectController->get_camera().setMoveSpeed(0.2f);
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Scene::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Scene::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Scene::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
	instance->sceneObjectController->get_camera().resize_projection((float)width, (float)height);
}



void Scene::cursor_callback(GLFWwindow* window, double x, double y)
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	if (instance->mousePress)
	{

		instance->sceneObjectController->get_camera().mouseMove(x, y, w, h);
		glfwSetCursorPos(window, (w / 2), (h / 2));
	}

	printf("cursor_callback [%.1f,%.1f] \n", x, y);
}

void Scene::button_callback(GLFWwindow* window, int button, int action, int mode) {
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		instance->mousePress = true;
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		glfwSetCursorPos(window, (w / 2), (h / 2));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		instance->mousePress = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		instance->sceneObjectController->add_or_remove_object();
	}


	if (action == GLFW_PRESS) printf("button_callback [Button = %d, action = %d, mode = %d]\n", button, action, mode);
}

void Scene::getWindowSize(int* width, int* height)
{
	glfwGetWindowSize(instance->window, width, height);
}

void Scene::main_loop()
{
	instance->sceneObjectController->init_vao_vbo_shader();
	int w, h;
	glfwGetWindowSize(instance->window, &w, &h);
	glfwSetCursorPos(instance->window, w / 2, h / 2);

	glfwSetInputMode(instance->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	instance->sceneObjectController->static_transformations();

	while (!glfwWindowShouldClose(instance->window)) {
		
		instance->sceneObjectController->dynamic_transformations();
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		instance->sceneObjectController->draw_objects();

		glfwPollEvents();
		glfwSwapBuffers(instance->window);
	}
}