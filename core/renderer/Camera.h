//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_CAMERA_H
#define LEARN_OPENGL_CAMERA_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
private:
    double mouseX;
    double mouseY;
public:
    //
    glm::vec3 position{};
    glm::vec3 toward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view{};
    glm::mat4 projection{};

    unsigned int width;
    unsigned int height;

    // 视角
    float fov;
    // 近平面
    float nearPlane;
    // 远平面
    float farPlane;

    float speed = 0.02;
    bool touched = false;

    Camera(int width, int height, glm::vec3 position, float fov, float near, float far);

    void UpdateMatrix();

    void OnInput(GLFWwindow* window);
};


#endif //LEARN_OPENGL_CAMERA_H
