#pragma once
#include <vector>
#include <demoShaderLoader.h>
#include <iostream>
#include "vertex.h"

class Mesh 
{
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader& shader);
private:
    unsigned int VBO, EBO;

    void setupMesh();
};