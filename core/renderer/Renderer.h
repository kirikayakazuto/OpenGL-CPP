//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_RENDERER_H
#define LEARN_OPENGL_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include "../scene/Scene.h"

class Renderer {
private:

    std::time_t nowTime{};

    GLFWwindow* CreateWindow(int width, int height) {
        // 初始化glfw
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        auto window = glfwCreateWindow(width, height, "learn opengl", nullptr, nullptr);
        if(window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, this->framebuffer_size_callback);
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        return window;
    }

    void ProcessInput() const {
        if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(this->window, true);
        }
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
public:

    GLFWwindow* window{};

    Renderer() {
        this->nowTime = std::time(nullptr);
    }

    void Init(int width, int height) {
        this->window = this->CreateWindow(width, height);
    }

    void MainLoop(Scene* scene) {
        while (!glfwWindowShouldClose(this->window)) {
            this->ProcessInput();

            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // 更新逻辑
            scene->OnUpdate(0);
            // 更新渲染
            scene->Draw();

            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }

        glfwTerminate();
    }

};


#endif //LEARN_OPENGL_RENDERER_H
