#pragma once
#include "VertexData.h"
#include "ShaderProgram.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

class Model
{
    VertexData* data = nullptr;
protected:
    GLuint VAO = 0;
    GLuint VBO = 0;
    unsigned int size = 0;
public:
    Model() = default;
    Model(const float* points, int n);
    virtual ~Model();
    virtual void draw();
    virtual bool create_vao_vbo();
};

