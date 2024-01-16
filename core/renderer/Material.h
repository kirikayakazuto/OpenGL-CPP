//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_MATERIAL_H
#define LEARN_OPENGL_MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Material {
private:
    std::unordered_map<std::string, Texture*> textureMap;
    std::unordered_map<std::string, double> doubleMap;
    std::unordered_map<std::string, const float*> matMap;
public:
    Shader* shader;

    Material(Shader* shader):
        shader(shader),
        textureMap(std::unordered_map<std::string , Texture*>()),
        matMap(std::unordered_map<std::string , const float*>()) {

    }

    void SetTexture(std::string key, Texture* val) {
        auto pair = std::pair<std::string, Texture*>(key, val);
        this->textureMap.insert(pair);
    }

    void SetUniformMat(std::string key, const float* val) {
        auto pair = std::pair<std::string, const float*>(key, val);
        this->matMap.insert(pair);
    }

    void Activate() {
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

    void UnActivate() {

    }
};


#endif //LEARN_OPENGL_MATERIAL_H
