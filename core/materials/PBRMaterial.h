//
// Created by 邓朗 on 2024/1/29.
//

#ifndef LEARN_OPENGL_PBRMATERIAL_H
#define LEARN_OPENGL_PBRMATERIAL_H

#include "../renderer/Material.h"
#include "../renderer/Texture.h"

class PBRMaterial : public Material {
private:

public:
    PBRMaterial(std::unordered_map<std::string, std::vector<std::string>>& textureMap): Material(new Shader("core/materials/shaders/pbr.vert","core/materials/shaders/pbr.frag")) {
        int index = 0;
        for (const auto &item: textureMap) {
            for(int i=0; i<item.second.size(); i++) {
                auto key = item.first + std::to_string(i);
                auto url = "assets/models/man/" + item.second[i];
                std::cout << "texture name: " << key << " : " << url << index << std::endl;
                this->SetTexture(key, new Texture(url, index++));
            }
        }
    }
};

#endif //LEARN_OPENGL_PBRMATERIAL_H
