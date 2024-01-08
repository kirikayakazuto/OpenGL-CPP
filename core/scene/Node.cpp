//
// Created by 邓朗 on 2024/1/4.
//

#include "Node.h"

#include <utility>

Node::Node(std::string _nodeName, Mesh& _mesh, Material& _material):
    nodeName(std::move(_nodeName)),
    mesh(&_mesh),
    material(&_material) {

    this->position = glm::vec3(0, 0, 0);
    this->scale = glm::vec3(1, 1, 1);
}

Node *Node::AddChild(Node *node) {
    this->children.push_back(node);
    return node;
}

Node *Node::GetChild(std::string nodeName) {
    for (const auto &item: this->children) {
        if (item->nodeName == nodeName) {
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

