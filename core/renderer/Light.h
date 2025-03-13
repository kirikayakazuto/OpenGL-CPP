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
    LightType type = Point;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;

    Light(const glm::vec3 position, const glm::vec3 color): position(position), color(color) {

    }

};

#endif //LEARN_OPENGL_LIGHT_H
