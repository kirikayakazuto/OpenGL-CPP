//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_NODE_H
#define LEARN_OPENGL_NODE_H

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include "Material.h"

class Node {
private:

public:
    // 位置
    glm::vec3 position;
    // 缩放
    glm::vec3 scale;
    // 父节点
    Node* parent;
    // 子节点
    std::vector<Node*> children;
    // 名称
    std::string name;
    // 顶点
    Mesh* mesh;
    // 材质
    Material* material;

    Node(std::string name);

    // 添加子节点
    Node* add_child(Node* node);

    // 获取子节点
    Node* get_child(std::string name);

    // 获取子节点
    Node* get_child(int index);

};


#endif //LEARN_OPENGL_NODE_H