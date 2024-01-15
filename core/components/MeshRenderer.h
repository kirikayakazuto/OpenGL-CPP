//
// Created by Bytedance on 2024/1/15.
// 渲染组件, 提供渲染能力
//

#ifndef LEARN_OPENGL_MESHRENDERER_H
#define LEARN_OPENGL_MESHRENDERER_H

#include "BaseComponent.h"
#include "../renderer/Mesh.h"
#include "../renderer/Material.h"

class MeshRenderer: public BaseComponent{
public:
    Mesh* mesh;
    Material* material;
};


#endif //LEARN_OPENGL_MESHRENDERER_H
