//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_SCENE_H
#define LEARN_OPENGL_SCENE_H

#include "Node.h"
#include "../renderer/Camera.h"

class Scene {
private:
    GLFWwindow* window;
public:
    Node* root{};
    Camera* camera;

    Scene(int width, int height, GLFWwindow* window);

    void Draw() const;

    void OnUpdate(float dt);
};


#endif //LEARN_OPENGL_SCENE_H
