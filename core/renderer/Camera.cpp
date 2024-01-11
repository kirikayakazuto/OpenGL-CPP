//
// Created by 邓朗 on 2024/1/6.
//

#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, float fov, float nearPlane, float farPlane) {
    this->width = width;
    this->height = height;
    this->position = position;
    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

void Camera::UpdateMatrix() {
    this->view = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);

    this->view = glm::lookAt(this->position, this->position + this->toward, this->up);
    this->projection = glm::perspective(glm::radians(this->fov), (float)this->width / this->height, nearPlane, farPlane);
}

void Camera::OnInput() {
    auto renderer = Renderer::GetInstance();
    if(glfwGetKey(renderer->window, GLFW_KEY_W) == GLFW_PRESS) {
        this->position += this->toward;
    }
}
