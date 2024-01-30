//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_TEXTUREMATERIAL_H
#define LEARN_OPENGL_TEXTUREMATERIAL_H

#include "../renderer/Material.h"
#include "../renderer/Texture.h"

class TextureMaterial: public Material {
private:
    Texture* mainTexture;
public:
    std::string url;

    TextureMaterial(const std::string& url):
        Material(new Shader("core/scene/shaders/default.vert","core/scene/shaders/default.frag")),
        url(url) {

        this->mainTexture = new Texture(url, 0);
        this->SetUniform("mainTexture", this->mainTexture);
    }

};


#endif //LEARN_OPENGL_TEXTUREMATERIAL_H
