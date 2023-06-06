#pragma once
#include "Model.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // aiSceneoutputdata structure
#include <assimp/postprocess.h> // Post processing flags
#include <string>
#include <iostream>

class ModelAssimp : public Model
{
	GLuint IBO = 0;
	VertexDataAssimp* data = nullptr;
	unsigned int* pIndices = nullptr;
	int indicesCount = 0;
	int size = 0;

public:
	ModelAssimp(const std::string& objFile);
	~ModelAssimp();
	void draw() override;
	bool create_vao_vbo() override;
};

