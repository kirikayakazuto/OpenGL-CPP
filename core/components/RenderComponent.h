//
// Created by Bytedance on 2024/1/15.
// 渲染组件, 提供渲染能力
//

#ifndef LEARN_OPENGL_RENDERCOMPONENT_H
#define LEARN_OPENGL_RENDERCOMPONENT_H

#include "../renderer/Mesh.h"
#include "../renderer/Material.h"

class RenderComponent {
public:
    Mesh* mesh;
    Material* material;
};


#endif //LEARN_OPENGL_RENDERCOMPONENT_H
