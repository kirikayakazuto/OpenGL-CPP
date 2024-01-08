//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_RENDERER_H
#define LEARN_OPENGL_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
private:
    GLFWwindow* window;
public:
    Renderer();

    void init(int width, int height);

    GLFWwindow* create_window(int width, int height);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void process_input();

    void main_loop();

};


#endif //LEARN_OPENGL_RENDERER_H
