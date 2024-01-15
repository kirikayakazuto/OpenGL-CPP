//
// Created by 邓朗 on 2024/1/4.
//

#include "Scene.h"


float vertices[] =
        { //     COORDINATES     /        COLORS      /   TexCoord  //
                -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
                -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
                0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
                0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
                0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 1, 4,
                1, 2, 4,
                2, 3, 4,
                3, 0, 4
        };

Material* CreateSpriteMaterial(const std::string& url) {
    auto shader = new Shader("core/scene/shaders/default.vert","core/scene/shaders/default.frag");
    auto material = new Material(shader);
    auto texture = new Texture(url, 0);
    material->SetTexture("mainTexture", texture);
    return material;
}

Scene::Scene(int width, int height, GLFWwindow* window) {
    this->window = window;
    this->camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 45.0f, 0.1f, 100.0f);

    this->root = new Node("Root");
    auto plane = this->root->AddComponent<Plane>();
    plane->SetMaterial(new TextureMaterial("assets/pop_cat.png"));

    auto com = this->root->GetComponent<Plane>();

    this->root->SetPosition(glm::vec3(0, 0, 0));
    this->root->SetScale(glm::vec3(1, 1, 1));
}

void WalkTree(Node* node, std::vector<Node*>& nodes) {
    nodes.push_back(node);
    for (const auto &item: node->children) {
        WalkTree(node, nodes);
    }
}

void Scene::Draw() const {
    glEnable(GL_DEPTH_TEST);
    std::vector<Node*> nodes;
    WalkTree(this->root, nodes);

    for (const auto &item: nodes) {
        auto meshRenderer = item->GetComponent<MeshRenderer>();
        glBindVertexArray(meshRenderer->mesh->GetVaoId());
        meshRenderer->material->SetUniformMat("u_cameraMatrix", glm::value_ptr(this->camera->projection * this->camera->view));
        meshRenderer->material->Activate();
        glDrawElements(GL_TRIANGLES, meshRenderer->mesh->indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void Scene::OnUpdate(float dt) {
    this->camera->OnInput(this->window);
    this->camera->UpdateMatrix();
}
