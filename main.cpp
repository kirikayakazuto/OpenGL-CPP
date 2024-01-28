#include <iostream>

#include "core/renderer/Renderer.h"
#include "core/scene/Scene.h"

int main() {
    // 初始化 renderer
    auto renderer = new Renderer();
    renderer->Init(1334, 750);

    auto scene = new Scene(1334, 750, renderer->window);
    renderer->MainLoop(scene);

    return 0;
}