#include "Camera.h"

Camera::Camera(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition)
{
	//this->shaders = std::vector<ShaderProgram*>();

	this->viewMatrix = viewMatrix;

	this->projectionMatrix = projectionMatrix;

	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->eye = cameraPosition;
	this->direction = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera()
{
	this->obs.clear();
}

glm::vec3& Camera::getEye()
{
	return this->eye;
}

glm::vec3& Camera::getDirection()
{
	return this->direction;
}

glm::mat4& Camera::getCamera()
{
	//vytvoření pohledové matice
	this->viewMatrix = glm::lookAt(eye, eye + direction, up);
	//this->set_changed_values(viewMatrix, "viewMatrix");
	//notify();
	return this->viewMatrix;
}

glm::mat4& Camera::get_projection_matrix()
{
	return this->projectionMatrix;
}

glm::mat4& Camera::get_view_matrix()
{
	return this->viewMatrix;
}

void Camera::frontMove()
{
	eye += this->moveSpeed * (glm::normalize(direction));
	//getCamera();
	notify();
}

void Camera::backMove()
{
	eye -= this->moveSpeed * (glm::normalize(direction));
	//getCamera();
	notify();
}

void Camera::leftMove() {
	//cross najde vektor kolmý na vektory direction a up
	eye -= this->moveSpeed * (glm::normalize(glm::cross(direction, up)));
	//getCamera();
	notify();
}

void Camera::rightMove() {
	eye += this->moveSpeed * (glm::normalize(glm::cross(direction, up)));
	//getCamera();
	notify();
}

void Camera::setMoveSpeed(float newMoveSpeed)
{
	this->moveSpeed = newMoveSpeed;
}

void Camera::mouseMove(double new_x, double new_y, int width, int height) {
	float rotX = this->mouseSpeed * (float)(new_y - (height / 2)) / height;
	float rotY = this->mouseSpeed * (float)(new_x - (width / 2)) / width;

	glm::vec3 newOrientation = glm::rotate(direction, glm::radians(- rotX), glm::normalize(glm::cross(direction, up)));
	// verifikace nov� pozice orientace kamery
	//angle vrátí úhel mezi vektory newOri a up
	if (abs(glm::angle(glm::normalize(newOrientation), this->up) - glm::radians(90.0f)) < glm::radians(85.0f))
	{
		this->direction = newOrientation;
	}
	this->direction = glm::rotate(this->direction, glm::radians(-rotY), this->up);

	notify();
}

void Camera::attach_shader(ShaderProgram* shader)
{
	this->attach(shader);
	//this->shaders.push_back(shader);
}

void Camera::unsubscribe_shader(ShaderProgram* shader)
{
	this->remove(shader);
}

bool Camera::search_shader(ShaderProgram* shader)
{/*
	if (std::find(shaders.begin(), shaders.end(), shader) != shaders.end())
		return true;
	else
		return false;
		*/
	return obs.find(shader) != obs.end();
}

void Camera::set_changed_values(glm::mat4& matrixNewValue, std::string matrixNewName)
{
	this->matrixNewName = matrixNewName;
	this->matrixNewValue = matrixNewValue;
	notify();
}

void Camera::resize_projection(float width, float height)
{
	//vyvoří projekční matici
	projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 10000.0f);
}
/*
void Camera::notify()
{
	for (ShaderProgram* s : shaders)
	{
		s->update(matrixNewValue, matrixNewName);
	}
}*/

void Camera::update()
{
	this->viewMatrix = glm::lookAt(eye, eye + direction, up);
	notify();
	/*
	this->set_changed_values(projectionMatrix, "projectionMatrix");
	this->getCamera(); */
}
