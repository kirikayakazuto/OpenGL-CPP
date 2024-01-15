//
// Created by 邓朗 on 2024/1/4.
//

#include "Material.h"

Material::Material(Shader* _shader):
    shader(_shader),
    textureMap(std::unordered_map<std::string , Texture*>()),
    matMap(std::unordered_map<std::string , const float*>()){

}

void Material::SetTexture(std::string key, Texture* val) {
    auto pair = std::pair<std::string, Texture*>(key, val);
    this->textureMap.insert(pair);
}

void Material::SetUniformMat(std::string key, const float* val) {
    auto pair = std::pair<std::string, const float*>(key, val);
    this->matMap.insert(pair);
}

void Material::Activate() {
    this->shader->Activate();

    for (const auto &item: this->textureMap) {
        auto texUni = glGetUniformLocation(this->shader->ID, item.first.c_str());
        glUniform1i(texUni, item.second->unit);
        item.second->Bind();
    }

    for (const auto &item: this->matMap) {
        auto uni = glGetUniformLocation(this->shader->ID, item.first.c_str());
        glUniformMatrix4fv(uni, 1, GL_FALSE, item.second);
    }

}
