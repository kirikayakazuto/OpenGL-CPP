//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_RENDERER_H
#define LEARN_OPENGL_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../scene/Scene.h"

class Renderer {
private:
    GLFWwindow* window;

public:
    Renderer();

    void Init(int width, int height);

    GLFWwindow* CreateWindow(int width, int height);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void ProcessInput();

    void MainLoop(Scene* scene);

    void Draw(Scene* scene);

};


#endif //LEARN_OPENGL_RENDERER_H
