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
    std::vector<Node*> nodes;

    void CollectTreeNode() {
        this->nodes.clear();
        std::stack<Node*> nodeStack;
        nodeStack.push(this->root);
        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();
            this->nodes.push_back(current);

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

        this->root->SetPosition(glm::vec3(1, 0, 0));
        this->root->SetScale(glm::vec3(1, 1, 1));
        this->root->SetRotation(glm::vec3(0, 0, 0));


        auto leftSprite = new Node("Sprite");
        auto plane2 = leftSprite->AddComponent<Plane>();
        plane2->SetMaterial(new TextureMaterial("assets/pop_cat.png"));
        leftSprite->SetPosition(glm::vec3(-1, 0, 0));


        auto rightSprite = new Node("Sprite");
        auto plane3 = rightSprite->AddComponent<Plane>();
        plane3->SetMaterial(new TextureMaterial("assets/tt.png"));
        rightSprite->SetPosition(glm::vec3(1, 0, 0));

        this->root->AddChild(rightSprite);
        this->root->AddChild(leftSprite);
    }

    void Draw() const {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
        CollectTreeNode();

        this->camera->OnInput(this->window);
        this->camera->UpdateMatrix();

        for (const auto &node: this->nodes) {
            for (const auto &com: node->components) {
                com->OnUpdate(dt);
            }
        }
    }
};


#endif //LEARN_OPENGL_SCENE_H
