#include <iostream>

#include "core/renderer/Renderer.h"
#include "core/scene/Node.h"

int main() {
    // 初始化 renderer
    std::unique_ptr<Renderer> renderer(new Renderer());
    renderer->init(800, 600);
    renderer->main_loop();

    // std::cout << "do draw" << std::endl;



    return 0;
}