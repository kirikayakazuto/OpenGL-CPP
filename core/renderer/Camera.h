//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_CAMERA_H
#define LEARN_OPENGL_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {

private:
    double mouseX{};
    double mouseY{};

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
    // 移动速度
    float speed = 0.02;
    //
    bool touched = false;

    Camera(const int width, const int height, const glm::vec3 position, const float fov, const float near, const float far) {
        this->width = width;
        this->height = height;
        this->position = position;
        this->fov = fov;
        this->nearPlane = near;
        this->farPlane = far;
    }

    void UpdateMatrix() {
        this->view = glm::mat4(1.0f);
        this->projection = glm::mat4(1.0f);

        this->view = glm::lookAt(this->position, this->position + this->toward, this->up);
        this->projection = glm::perspective(glm::radians(this->fov), static_cast<float>(this->width) / static_cast<float>(this->height), nearPlane, farPlane);
    }

    void OnInput(GLFWwindow* window) {
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

            constexpr float rotateSpeed = 0.1;
            const auto dx = (this->mouseX - currMouseX) * rotateSpeed;
            const auto dy = (this->mouseY - currMouseY) * rotateSpeed;

            this->mouseX = currMouseX;
            this->mouseY = currMouseY;

            if(!this->touched) {
                this->touched = true;
                return;
            }

//            auto newToward = glm::rotate(this->toward, glm::radians((float)dx), this->up);
//            auto right = glm::normalize(glm::cross(newToward, this->up));
//            auto newUp = glm::rotate(this->up, glm::radians((float)dy), right);
//            newToward = glm::rotate(newToward, glm::radians((float)dy), right);

            auto newToward = glm::rotate(this->toward, glm::radians(static_cast<float>(dx)), glm::vec3(0, 1, 0));
            auto right = glm::normalize(glm::cross(newToward, this->up));
            auto newUp = glm::rotate(this->up, glm::radians(static_cast<float>(dy)), glm::vec3(1, 0, 0));
             newToward = glm::rotate(newToward, glm::radians(static_cast<float>(dy)), glm::vec3(1, 0, 0));

            this->toward = newToward;
            this->up = newUp;

        }
        else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            if(this->touched) {
                this->touched = false;
            }
        }
    }
};


#endif //LEARN_OPENGL_CAMERA_H
