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
    this->projection = glm::perspective(glm::radians(this->fov), (float)(this->width) / (float)this->height, nearPlane, farPlane);
}

void Camera::OnInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->position += this->speed * this->toward;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->position -= this->speed * this->toward;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
         this->position -= this->speed * glm::normalize(glm::cross(this->toward, this->up));
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        this->position += this->speed * glm::normalize(glm::cross(this->toward, this->up));
    }

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        this->position -= this->speed * this->up;
    }

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        this->position += this->speed * this->up;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double currMouseX;
        double currMouseY;
        glfwGetCursorPos(window, &currMouseX, &currMouseY);

        float rotateSpeed = 0.1;
        auto dx = (this->mouseX - currMouseX) * rotateSpeed;
        auto dy = (this->mouseY - currMouseY) * rotateSpeed;

        this->mouseX = currMouseX;
        this->mouseY = currMouseY;

        if(!this->touched) {
            this->touched = true;
            return;
        }

        auto newToward = glm::rotate(this->toward, glm::radians((float)dx), this->up);
        auto right = glm::normalize(glm::cross(newToward, this->up));
        auto newUp = glm::rotate(this->up, glm::radians((float)dy), right);
        newToward = glm::rotate(newToward, glm::radians((float)dy), right);

         this->toward = newToward;
         this->up = newUp;

    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        if(this->touched) {
            this->touched = false;
        }
    }
}
