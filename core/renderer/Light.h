//
// Created by 邓朗 on 2024/1/16.
//

#ifndef LEARN_OPENGL_LIGHT_H
#define LEARN_OPENGL_LIGHT_H

#include <glm/glm.hpp>

enum LightType {
    Direction,
    Point
};

class Light {
private:
public:
    LightType type = Direction;
    glm::vec3 position;
    glm::vec3 direction;
};

#endif //LEARN_OPENGL_LIGHT_H
