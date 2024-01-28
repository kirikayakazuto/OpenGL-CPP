//
// Created by Bytedance on 2024/1/15.
// 渲染组件, 提供渲染能力
//

#ifndef LEARN_OPENGL_MESHRENDERER_H
#define LEARN_OPENGL_MESHRENDERER_H

#include "Component.h"
#include "../renderer/Mesh.h"
#include "../renderer/Material.h"


class MeshRenderer: public Component {
public:
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
    
    void OnStart() override {
        std::cout << "call mesh renderer on start" << std::endl;
    }

    void OnUpdate(double dt) override {
        // std::cout << "on update: " << dt << std::endl;
    }

};


#endif //LEARN_OPENGL_MESHRENDERER_H
