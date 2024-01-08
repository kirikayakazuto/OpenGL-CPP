//
// Created by 邓朗 on 2024/1/6.
//

#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
    this->width = width;
    this->height = height;
    this->position = position;
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane) {

}

void Camera::OnInput(GLFWwindow *window) {

}
