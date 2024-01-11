#include <iostream>

#include "core/renderer/Renderer.h"
#include "core/scene/Scene.h"

int main() {
    // 初始化 renderer
    auto renderer = Renderer::GetInstance();
    renderer->Init(800, 600);

    auto scene = new Scene(800, 600);
    renderer->MainLoop(scene);

    // std::cout << "do draw" << std::endl;




    return 0;
}