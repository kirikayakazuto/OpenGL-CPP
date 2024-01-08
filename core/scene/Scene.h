//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_SCENE_H
#define LEARN_OPENGL_SCENE_H

#include "Node.h"

class Scene {
public:
    Node* root{};
    Scene();

    void Draw() const;
};


#endif //LEARN_OPENGL_SCENE_H
