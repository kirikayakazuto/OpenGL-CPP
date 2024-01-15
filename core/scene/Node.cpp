//
// Created by 邓朗 on 2024/1/4.
//

#include "Node.h"

#include <utility>

Node::Node(std::string _nodeName): nodeName(std::move(_nodeName)) {

    this->position = glm::vec3(0, 0, 0);
    this->scale = glm::vec3(1, 1, 1);
}

Node *Node::AddChild(Node *node) {
    if(node->parent != nullptr) {
        auto local_children = node->parent->children;
        auto it = std::find(local_children.begin(), local_children.end(), node);
        if (it != local_children.end()) {
            local_children.erase(it);
        }
    }
    this->children.push_back(node);
    node->parent = this;
    return node;
}

Node *Node::GetChild(const std::string& key) {
    for (const auto &item: this->children) {
        if (item->nodeName == key) {
            return item;
        }
    }
    return nullptr;
}

Node *Node::GetChild(int index) {
    return this->children[index];
}

glm::vec3 Node::GetPosition() {
    return this->position;
}

glm::vec3 Node::GetScale() {
    return this->scale;
}

void Node::SetPosition(glm::vec3 val) {
    this->position = val;
}

void:: Node::SetScale(glm::vec3 val) {
    this->scale = val;
}

template<class T_Component>
T_Component *Node::GetComponent() {
    for (const auto &item: this->components) {
        if(dynamic_cast<T_Component>(item)) {
            return item;
        }
    }
    return nullptr;
}

template <class T_Component>
T_Component* Node::AddComponent() {
    static_assert(std::is_base_of<Component, T_Component>::value, "T must bt subclass of Component");
    auto com = T_Component();
    this->components.push_back(com);
    return com;
}
//
//template <class T_Component>
//Component* Node::GetComponent() {
//
//}



