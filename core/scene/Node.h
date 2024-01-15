//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_NODE_H
#define LEARN_OPENGL_NODE_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "../components/Component.h"

class Node {
private:
    // 位置
    glm::vec3 position{};
    // 缩放
    glm::vec3 scale{};

    glm::vec3 rotation{};
public:
    // 父节点
    Node* parent{};
    // 子节点
    std::vector<Node*> children;
    // 名称
    std::string nodeName;

    Node(std::string nodeName);
    // 组件
    std::vector<Component*> components;
    // 添加子节点
    Node* AddChild(Node* node);
    // 获取子节点
    Node* GetChild(const std::string& key);
    // 获取子节点
    Node* GetChild(int index);

    glm::vec3 GetPosition();

    glm::vec3 GetScale();

    void SetPosition(glm::vec3 val);

    void SetScale(glm::vec3 val);

    template <class T_Component>
    T_Component* AddComponent();

    template <class T_Component>
    T_Component* GetComponent();

};


#endif //LEARN_OPENGL_NODE_H
