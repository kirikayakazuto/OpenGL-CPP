//
// Created by 邓朗 on 2024/1/4.
//

#include "Node.h"

Node *Node::add_child(Node *node) {
    this->children.push_back(node);
    return node;
}

Node::Node(const std::string name) {
    this->name = name;
    this->position = glm::vec3(0, 0, 0);
    this->scale = glm::vec3(1, 1, 1);
}

Node *Node::get_child(std::string name) {
    for (const auto &item: this->children) {
        if (item->name == name) {
            return item;
        }
    }
    return nullptr;
}

Node *Node::get_child(int index) {
    return this->children[index];
}
