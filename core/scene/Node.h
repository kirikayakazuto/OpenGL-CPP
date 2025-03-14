//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_NODE_H
#define LEARN_OPENGL_NODE_H

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../components/Component.h"
#include "../components/MeshRenderer.h"

class Node {
private:
    // 位置
    glm::vec3 position = glm::vec3(0, 0, 0);
    // 缩放
    glm::vec3 scale = glm::vec3(1, 1, 1);

    glm::vec3 rotation = glm::vec3(0, 0, 0);
public:
    // 父节点
    Node* parent{};
    // 子节点
    std::vector<Node*> children{};
    // 名称
    std::string nodeName;
    // 组件
    std::vector<Component*> components{};
    // 世界矩阵
    glm::mat4 worldMatrix = glm::mat4(1.0f);

    Node(std::string nodeName): nodeName(std::move(nodeName)) {

    }

    // 添加子节点
    Node* AddChild(Node* node) {
        if(node->parent != nullptr) {
            auto local_children = node->parent->children;
            if (const auto it = std::find(local_children.begin(), local_children.end(), node); it != local_children.end()) {
                local_children.erase(it);
            }
        }
        this->children.push_back(node);
        node->parent = this;

        for (const auto &item: node->components) {
            item->OnInit();
        }

        return node;
    }
    // 获取子节点
    Node* GetChild(const std::string& key) const {
        for (const auto &item: this->children) {
            if (item->nodeName == key) {
                return item;
            }
        }
        return nullptr;
    }
    // 获取子节点
    Node* GetChild(int index) const {
        return this->children[index];
    }

    glm::vec3 GetPosition() const {
        return this->position;
    }

    glm::vec3 GetScale() const {
        return this->scale;
    }

    void SetPosition(glm::vec3 val) {
        this->position = val;
    }

    void SetScale(glm::vec3 val) {
        this->scale = val;
    }

    void SetRotation(glm::vec3 val) {
        this->rotation = val;
    }

    void UpdateMatrix() {
        this->worldMatrix = glm::mat4(1.0f);
        this->worldMatrix = glm::translate(this->worldMatrix, this->position);

        this->worldMatrix = glm::rotate(this->worldMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        this->worldMatrix = glm::rotate(this->worldMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        this->worldMatrix = glm::rotate(this->worldMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        this->worldMatrix = glm::scale(this->worldMatrix, this->scale);
    }

    template <class T_Component>
    T_Component* AddComponent() {
        static_assert(std::is_base_of_v<Component, T_Component>, "T must bt subclass of Component");
        auto com = new T_Component();
        this->components.push_back(com);
        return com;
    }

    template <class T_Component>
    T_Component* GetComponent() {
        static_assert(std::is_base_of_v<Component, T_Component>, "T must be a subclass of Component");
        for (auto &item : this->components) {
            if (std::is_base_of_v<MeshRenderer, T_Component>) {
                if (auto component = dynamic_cast<T_Component*>(item)) {
                    return component;
                }
            }
        }
        return nullptr;
    }

};


#endif //LEARN_OPENGL_NODE_H
