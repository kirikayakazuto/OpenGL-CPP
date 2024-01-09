//
// Created by 邓朗 on 2024/1/4.
//

#include "Material.h"

Material::Material(Shader* _shader):
    shader(_shader),
    textureMap(std::unordered_map<std::string , Texture*>()) {

}

void Material::SetTexture(std::string textureName, Texture *texture) {
    auto pair = std::pair<std::string, Texture*>(textureName, texture);
    this->textureMap.insert(pair);
}

void Material::ActiveTextures() {
    for (const auto &item: this->textureMap) {
        item.second->Bind();
        auto texUni = glGetUniformLocation(this->shader->ID, item.first.c_str());
        glUniform1i(texUni, item.second->unit);
    }
}
