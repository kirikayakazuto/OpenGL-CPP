//
// Created by 邓朗 on 2024/1/28.
//

#ifndef LEARN_OPENGL_SINGLEMATERIAL_H
#define LEARN_OPENGL_SINGLEMATERIAL_H

#include "../renderer/Material.h"
#include "../renderer/Texture.h"

class SingleMaterial : public Material {
public:
    SingleMaterial():
        Material(new Shader("core/scene/shaders/single.vert","core/scene/shaders/single.frag")){

    }
};

#endif //LEARN_OPENGL_SINGLEMATERIAL_H
