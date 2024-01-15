//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_TEXTUREMATERIAL_H
#define LEARN_OPENGL_TEXTUREMATERIAL_H

#include "../renderer/Material.h"
#include "../renderer/Texture.h"

class TextureMaterial: public Material{
private:
    Texture* mainTexture;
public:
    std::string url;

    TextureMaterial(const std::string& url);

};


#endif //LEARN_OPENGL_TEXTUREMATERIAL_H
