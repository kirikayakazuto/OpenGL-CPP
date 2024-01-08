//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_MATERIAL_H
#define LEARN_OPENGL_MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include <unordered_map>

class Material {
public:

    Shader* shader;

    std::unique_ptr<std::unordered_map<std::string , Texture&>> textureMap;

    std::unique_ptr<std::unordered_map<std::string , double>> doubleMap;

    std::unique_ptr<std::unordered_map<std::string, std::variant<int, double>>> uniformMap;

    Material(Shader* shader);

    void SetTexture(std::string textureName, Texture& texture);
};


#endif //LEARN_OPENGL_MATERIAL_H
