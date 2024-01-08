#include <iostream>

#include "core/renderer/Renderer.h"
#include "core/scene/Scene.h"

int main() {
    // 初始化 renderer
    std::unique_ptr<Renderer> renderer(new Renderer());
    renderer->Init(800, 600);

    auto scene = new Scene();
    renderer->MainLoop(scene);

    // std::cout << "do draw" << std::endl;




    return 0;
}