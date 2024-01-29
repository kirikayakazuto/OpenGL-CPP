//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_RENDERER_H
#define LEARN_OPENGL_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../scene/Scene.h"
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION	// Use GL3 implementation.
#include <nanovg_gl.h>


class Renderer {
private:

    NVGcontext* vg;
    std::vector<int> images;
    int width;
    int height;

    GLFWwindow* CreateWindow(int width, int height) {
        this->width = width;
        this->height = height;
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

    void InitNanovg() {
        this->vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        auto fontNormal = nvgCreateFont(this->vg, "sans", "assets/fonts/Roboto-Regular.ttf");
        auto fontEmoji = nvgCreateFont(this->vg, "emoji", "assets/fonts/NotoEmoji-Regular.ttf");
        nvgAddFallbackFontId(this->vg, fontNormal, fontEmoji);
        std::string icons[] = {"addict.jpg", "backToBasics.jpg", "ballAndCup.jpg"};
        std::string baseUrl = "assets/icons/";
        for (const auto &item: icons) {
            auto image = nvgCreateImage(this->vg, (baseUrl + item).c_str(), 0);
            this->images.push_back(image);
        }
    }
public:
    GLFWwindow* window{};

    Renderer() {
    }

    void Init(int width, int height) {
        this->window = this->CreateWindow(width, height);
        this->InitNanovg();
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

            nvgBeginFrame(this->vg, width * 1.0f, height * 1.0f, 1.0f);

            nvgBeginPath(this->vg);
            nvgRect(vg, 200, 100, 100, 100);
            nvgFillColor(this->vg, nvgRGBA(255, 192, 0, 255));
            nvgFill(this->vg);

            nvgBeginPath(this->vg);
            nvgRect(this->vg, 100,100, 120,30);
            nvgCircle(this->vg, 120,120, 5);
            nvgPathWinding(this->vg, NVG_HOLE);	// Mark circle as a hole.
            nvgFillColor(this->vg, nvgRGBA(255,192,0,255));
            nvgFill(this->vg);

            nvgFontSize(this->vg, 36.0f);
            nvgFontFace(this->vg, "sans");
            nvgTextAlign(this->vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
            nvgFillColor(this->vg, nvgRGBA(255, 255, 255, 255));
            nvgText(this->vg, 100.0f, 100.0f, "Hello OpenGL!", nullptr);

            auto startX = 100;
            for (int i=0; i<this->images.size(); i++) {
                auto x = startX + 200 * i;
                auto y = 200;
                nvgBeginPath(this->vg);
                nvgRect(this->vg, x, y, 100, 100);
                nvgFillPaint(this->vg, nvgImagePattern(this->vg, x, y, 200, 200, 0, this->images[i], 1));
                nvgFill(this->vg);
            }
            nvgEndFrame(this->vg);

            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }

        nvgDeleteGL3(this->vg);
        glfwTerminate();
    }

};


#endif //LEARN_OPENGL_RENDERER_H
