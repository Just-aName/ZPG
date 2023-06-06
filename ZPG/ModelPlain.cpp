#include "ModelPlain.h"
ModelPlain::ModelPlain(const float* points, int size)
{
	this->VAO = -1;
	this->VBO = -1;
	this->size = size / 3;
	this->data = new Point[size / 3];
	for (int i = 0, j = 0; i < size; i = i + 3, j++)
	{
		this->data[j].x = points[i];
		this->data[j].y = points[i + 1];
		this->data[j].z = points[i + 2];
	}
}

ModelPlain::~ModelPlain()
{
	if (this->data != nullptr)
		delete[] this->data;

}

bool ModelPlain::create_vao_vbo()
{
	if (this->data != nullptr)
	{
		//vertex buffer object (VBO)
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * this->size, &this->data[0].x, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)0);

		if (VAO != -1)
			return true;
	}
	return false;
}