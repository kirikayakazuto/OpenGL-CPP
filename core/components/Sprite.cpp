//
// Created by Bytedance on 2024/1/15.
//

#include "Sprite.h"

Sprite::Sprite(const std::string &url) {
    this->url = url;
    auto tex = new Texture(url, 0);
    material->SetTexture("mainTexture", tex);
}
