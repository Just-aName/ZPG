#include "ModelAssimp.h"

ModelAssimp::ModelAssimp(const std::string& objFile)
{
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

    const aiScene* scene = importer.ReadFile(objFile, importOptions);

    if (scene)
    { //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());

            aiColor4D d;

            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);

        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
        {
            aiMesh* mesh = scene->mMeshes[i];

            Vertex* pVertexes = new Vertex[mesh->mNumVertices];
            std::memset(pVertexes, 0, sizeof(Vertex) * mesh->mNumVertices);

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions())
                {
                    pVertexes[i].Position[0] = mesh->mVertices[i].x;
                    pVertexes[i].Position[1] = mesh->mVertices[i].y;
                    pVertexes[i].Position[2] = mesh->mVertices[i].z;
                }

                if (mesh->HasNormals())
                {
                    pVertexes[i].Normal[0] = mesh->mNormals[i].x;
                    pVertexes[i].Normal[1] = mesh->mNormals[i].y;
                    pVertexes[i].Normal[2] = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0))
                {
                    pVertexes[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    pVertexes[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }

                if (mesh->HasTangentsAndBitangents())
                {
                    pVertexes[i].Tangent[0] = mesh->mTangents[i].x;
                    pVertexes[i].Tangent[1] = mesh->mTangents[i].y;
                    pVertexes[i].Tangent[2] = mesh->mTangents[i].z;
                }

            }

            unsigned int* pIndices = nullptr;

            if (mesh->HasFaces())
            {

                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++)
                {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &IBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertexes, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(VAO);

            indicesCount = mesh->mNumFaces * 3;

            GLuint  err = glGetError();
            if (err != GL_NO_ERROR)
            {
                fprintf(stderr, "OpenGL error %u: %s\n", err, gluErrorString(err));
            }

            indicesCount = mesh->mNumFaces * 3;

            delete[] pVertexes;
            delete[] pIndices;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", objFile.c_str(), importer.GetErrorString());
        exit(1);
    }
}

ModelAssimp::~ModelAssimp()
{
    if (this->data != nullptr)
        delete[] this->data;
    //delete[] pIndices;
}

void ModelAssimp::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}

bool ModelAssimp::create_vao_vbo()
{
    /*
    if (this->data != nullptr)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataAssimp) * size, &this->data[0].point.x, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataAssimp), (GLvoid*)(0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataAssimp), (GLvoid*)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexDataAssimp), (GLvoid*)(6 * sizeof(GLfloat)));
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataAssimp), (GLvoid*)(8 * sizeof(GLfloat)));
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesCount, pIndices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(VAO);



        GLuint  err = glGetError();
        if (err != GL_NO_ERROR)
        {
            fprintf(stderr, "OpenGL error %u: %s\n", err, gluErrorString(err));
        }
        glBindVertexArray(0);

        if (VAO != -1)
            return true;
    }
    return false;*/
    return true;
}
