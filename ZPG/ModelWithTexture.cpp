#include "ModelWithTexture.h"

ModelWithTexture::ModelWithTexture(const float* points, int size)
{
	this->VAO = -1;
	this->VBO = -1;
	this->size = size / 8;
	this->data = new VertexDataTexture[size / 8];
	for (int i = 0, j = 0; i < size; i = i + 8, j++)
	{
		this->data[j].point.x = points[i];
		this->data[j].point.y = points[i + 1];
		this->data[j].point.z = points[i + 2];
		this->data[j].normal.x = points[i + 3];
		this->data[j].normal.y = points[i + 4];
		this->data[j].normal.z = points[i + 5];
		this->data[j].texPoint.x = points[i + 6];
		this->data[j].texPoint.y = points[i + 7];
	}
}

ModelWithTexture::~ModelWithTexture()
{
	if (this->data != nullptr)
		delete[] this->data;
	
}

bool ModelWithTexture::create_vao_vbo()
{
	if (this->data != nullptr)
	{
		//vertex buffer object (VBO)
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataTexture) * this->size, &this->data[0].point.x, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glEnableVertexAttribArray(1); //enable vertex attributes
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataTexture), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataTexture), (GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexDataTexture), (GLvoid*)(6 * sizeof(float)));

		if (VAO != -1)
			return true;
	}
	return false;
}
