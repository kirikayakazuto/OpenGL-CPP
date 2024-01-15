//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_SPRITE_H
#define LEARN_OPENGL_SPRITE_H

#include "RenderComponent.h"
#include "../renderer/Texture.h"

class Sprite: public RenderComponent{
private:
    std::string url;
public:
    Texture* texture;

    Sprite(const std::string& url);
};


#endif //LEARN_OPENGL_SPRITE_H
