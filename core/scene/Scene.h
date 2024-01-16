//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_SCENE_H
#define LEARN_OPENGL_SCENE_H

#include "Node.h"
#include "../renderer/Camera.h"
#include "../components/Plane.h"
#include "../components/MeshRenderer.h"
#include "../materials/TextureMaterial.h"
#include <stack>

class Scene {
private:
    GLFWwindow* window;

    static void WalkTree(Node* node, std::vector<Node*>& nodes) {
        std::stack<Node*> nodeStack;
        nodeStack.push(node);
        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();
            nodes.push_back(current);

            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                nodeStack.push(*it);
            }
        }
    }
public:
    Node* root{};
    Camera* camera;

    Scene(int width, int height, GLFWwindow* window) {
        this->window = window;
        this->camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 45.0f, 0.1f, 100.0f);

        this->root = new Node("Root");
        auto plane = this->root->AddComponent<Plane>();
        plane->SetMaterial(new TextureMaterial("assets/pop_cat.png"));

        this->root->SetPosition(glm::vec3(1, 0, 0));
        this->root->SetScale(glm::vec3(1, 1, 1));
        this->root->SetRotation(glm::vec3(0, 0, 0));


        auto sprite = new Node("Sprite");
        this->root->AddChild(sprite);
    }

    void Draw() const {
        glEnable(GL_DEPTH_TEST);
        std::vector<Node*> nodes;
        Scene::WalkTree(this->root, nodes);

        for (const auto &item: nodes) {
            auto meshRenderer = item->GetComponent<MeshRenderer>();
            if(!meshRenderer) continue;
            item->UpdateMatrix();
            glBindVertexArray(meshRenderer->mesh->GetVaoId());
            meshRenderer->material->SetUniformMat("u_worldMatrix", glm::value_ptr(item->worldMatrix));
            meshRenderer->material->SetUniformMat("u_cameraMatrix", glm::value_ptr(this->camera->projection * this->camera->view));
            meshRenderer->material->Activate();
            glDrawElements(GL_TRIANGLES, (GLsizei)meshRenderer->mesh->indices.size(), GL_UNSIGNED_INT, 0);
        }
    }

    void OnUpdate(float dt) {
        this->camera->OnInput(this->window);
        this->camera->UpdateMatrix();
    }
};


#endif //LEARN_OPENGL_SCENE_H
