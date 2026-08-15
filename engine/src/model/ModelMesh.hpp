#pragma once
#include"glm/vec3.hpp"
#include"glm/glm.hpp"
#include<vector>
#include<string>

struct ModelVertex{
    glm::vec3 position{0.0f};
    glm::vec3 normal{0.0f,1.0f,0.0f}; //per face normal
    glm::vec2 uv{0.0f};
};


//this represent the whole 3d model
struct LoadedModel{

    std::vector<ModelVertex> vertices;
    std::vector<uint32_t> indices;
    std::string diffuseTexturePath;

};