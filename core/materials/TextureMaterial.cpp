//
// Created by Bytedance on 2024/1/15.
//

#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(const std::string& url) :
    Material(new Shader("core/scene/shaders/default.vert","core/scene/shaders/default.frag")),
    url(url) {

    this->mainTexture = new Texture(url, 0);
    this->SetTexture("mainTexture", this->mainTexture);
}
