#include "Model.h"

Model::Model(const float* points, int size)
{
	this->VAO = -1;
	this->VBO = -1;
	this->size = size / 6;
	this->data = new VertexData[size / 6];
	for (int i = 0, j = 0; i < size; i = i + 6, j++)
	{
		this->data[j].point.x = points[i];
		this->data[j].point.y = points[i+1];
		this->data[j].point.z = points[i+2];
		this->data[j].normal.x = points[i+3];
		this->data[j].normal.y = points[i+4];
		this->data[j].normal.z = points[i+5];
	}
}

Model::~Model()
{
	if (this->data != nullptr)
		delete[] this->data;
}


void Model::draw()
{
	glBindVertexArray(VAO);
	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, this->size); //mode,first,count
}

bool Model::create_vao_vbo()
{
	if (this->data != nullptr)
	{
		//vertex buffer object (VBO)
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * this->size, &this->data[0].point.x, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glEnableVertexAttribArray(1); //enable vertex attributes
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(sizeof(float) * 3));

		if (VAO != -1)
			return true;
	}
	return false;
}

