//
// Created by 邓朗 on 2024/1/4.
//

#include "Scene.h"


float vertices[] =
        { //     COORDINATES     /        COLORS      /   TexCoord  //
                -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
                -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
                0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
                0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 2, 1, // Upper triangle
                0, 3, 2 // Lower triangle
        };


Scene::Scene(int width, int height) {
    this->camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 45.0f, 0.1f, 100.0f);
    // 初始化mesh
    std::vector<AttributeFormat> attribute = {{ "a_position", 3 }, { "a_color", 3 }, {"a_uv", 2}};

    std::vector<float> vertexs = {vertices, vertices + sizeof(vertices) / sizeof(float )};
    std::vector<GLuint> indexs(indices, indices + sizeof(indices) / sizeof(GLuint));
    auto mesh = new Mesh(attribute, vertexs, indexs);

    // 初始化shader
    auto shader = new Shader("core/scene/shaders/default.vert","core/scene/shaders/default.frag");
    auto material = new Material(shader);

    auto texture = new Texture("assets/pop_cat.png", 0);
    material->SetTexture("mainTexture", texture);

    this->root = new Node("Root", mesh, material);
    this->root->SetPosition(glm::vec3(0, 0, 0));
    this->root->SetScale(glm::vec3(1, 1, 1));
}

void Scene::Draw() const {
    this->root->Draw();
}

void Scene::OnUpdate(double dt) {
    this->camera->OnInput();
    this->camera->UpdateMatrix();
    this->root->material->SetTexture()
}
