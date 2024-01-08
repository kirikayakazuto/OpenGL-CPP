//
// Created by 邓朗 on 2024/1/4.
//

#include "Renderer.h"
#include <iostream>

Renderer::Renderer() {

}

GLFWwindow *Renderer::CreateWindow(int width, int height) {
    // 初始化glfw
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, "learn opengl", nullptr, nullptr);
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

void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::ProcessInput() {
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, true);
    }
}

void Renderer::Init(int width, int height) {
    this->window = this->CreateWindow(width, height);
}

void Renderer::MainLoop(Scene* scene) {
    while (!glfwWindowShouldClose(this->window)) {
        this->ProcessInput();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->Draw(scene);

        glfwPollEvents();
        glfwSwapBuffers(this->window);
    }

    glfwTerminate();
}


void Renderer::Draw(Scene* scene) {
    scene->Draw();
}
