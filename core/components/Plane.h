//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_PLANE_H
#define LEARN_OPENGL_PLANE_H

#include "MeshRenderer.h"
#include "../materials/TextureMaterial.h"

std::vector<Vertex> vertices = {
        {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
        {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
        {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
        {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
};

std::vector<GLuint> indices = {0, 1, 2, 0, 2, 3};

class Plane: public MeshRenderer{
public:
    Plane(): MeshRenderer() {
        std::vector<AttributeFormat> attribute = {
                { "a_position", 3 },
                {"a_normal", 3},
                {"a_uv", 2},
                {"a_tangent", 3},
                {"a_bitangent", 3}
        };
        this->meshes.emplace_back(attribute, vertices, indices);
    }

    void SetMaterial(TextureMaterial m) {
        this->materials.push_back(m);
    }

    void OnStart() override {
        std::cout << "call Plane on start" << std::endl;
    }
};


#endif //LEARN_OPENGL_PLANE_H
