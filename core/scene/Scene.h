//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_SCENE_H
#define LEARN_OPENGL_SCENE_H

#include "Node.h"
#include "../renderer/Camera.h"
#include "../components/Plane.h"
#include "../components/Cube.h"
#include "../components/MeshRenderer.h"
#include "../materials/TextureMaterial.h"
#include <stack>
#include "../components/Model.h"
#include "../renderer/Light.h"

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
    Light* light;


    Scene(int width, int height, GLFWwindow* window) {
        this->window = window;
        this->camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 45.0f, 0.1f, 100.0f);
        this->light = new Light(glm::vec3(3.0f, 3.0f, -10.0f), glm::vec3(1.0f, 1.0f, 1.0f));


        this->root = new Node("Root");
        this->root->SetPosition(glm::vec3(1, 0, 0));
        this->root->SetScale(glm::vec3(1, 1, 1));
        this->root->SetRotation(glm::vec3(0, 0, 0));

        auto lightCube = new Node("CubeLight");
        lightCube->AddComponent<Cube>();
        lightCube->SetPosition(this->light->position);

        this->root->AddChild(lightCube);

        auto leftSprite = new Node("Sprite");
        auto plane2 = leftSprite->AddComponent<Plane>();
        plane2->SetMaterial(TextureMaterial("assets/pop_cat.png"));
        leftSprite->SetPosition(glm::vec3(-1, 0, 0));
        leftSprite->SetScale(glm::vec3(2, 1, 1));

        auto rightSprite = new Node("Sprite");
        auto plane3 = rightSprite->AddComponent<Plane>();
        plane3->SetMaterial(TextureMaterial("assets/tt.png"));
        rightSprite->SetPosition(glm::vec3(1, 0, 0));
        rightSprite->SetRotation(glm::vec3(0, 45, 0));

        this->root->AddChild(rightSprite);
        this->root->AddChild(leftSprite);

        auto m = new Node("Model");
        auto com = m->AddComponent<Model>();
        m->SetPosition(glm::vec3(0, -8, -20));
        this->root->AddChild(m);
    }

    void Draw() const {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);
//        glFrontFace(GL_CCW);

        for (const auto &item: nodes) {
            auto meshRenderer = item->GetComponent<MeshRenderer>();
            if(!meshRenderer) continue;
            for(int i=0; i<meshRenderer->meshes.size(); i++) {
                auto mesh = meshRenderer->meshes[i];
                auto material = meshRenderer->materials[i];
                glBindVertexArray(mesh.GetVaoId());
                material.SetUniform("u_worldMatrix", item->worldMatrix);
                material.SetUniform("u_cameraMatrix", this->camera->projection * this->camera->view);
                material.SetUniform("camera.position", this->camera->position);
                material.SetUniform("light.position", this->light->position);
                material.SetUniform("light.color", this->light->color);
                material.SetUniform("light.shininess", 1.0f);

                material.Activate();
                glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
            }
        }
    }

    void OnUpdate(float dt) {
        CollectTreeNode();

        this->camera->OnInput(this->window);
        this->camera->UpdateMatrix();

        for (const auto &node: this->nodes) {
            node->UpdateMatrix();
            for (const auto &com: node->components) {
                com->OnUpdate(dt);
            }
        }
    }
};


#endif //LEARN_OPENGL_SCENE_H
