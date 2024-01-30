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
    std::unordered_map<std::string, std::variant<float, glm::vec3, glm::mat4, Texture*>> uniformMap;
public:
    Shader* shader;

    Material(Shader* shader): shader(shader) {

    }

    void SetUniform(std::string key, std::variant<float, glm::vec3, glm::mat4, Texture*> value) {
        auto pair = std::pair<std::string, std::variant<float, glm::vec3, glm::mat4, Texture*>>(key, value);
        this->uniformMap.insert(pair);
    }

    void SetCamera() {

    }

    void SetLight() {

    }

    void Activate() {
        this->shader->Activate();

        for (const auto &item: this->uniformMap) {
            if(std::holds_alternative<float>(item.second)) {
                auto value = std::get<float>(item.second);
                auto uni = glGetUniformLocation(this->shader->ID, item.first.c_str());
                glUniform1f(uni, value);
            }
            if(std::holds_alternative<glm::vec3>(item.second)) {
                auto value = std::get<glm::vec3>(item.second);
                auto uni = glGetUniformLocation(this->shader->ID, item.first.c_str());
                glUniform3fv(uni, 1, &value[0]);
            }
            if(std::holds_alternative<glm::mat4>(item.second)) {
                auto value = std::get<glm::mat4>(item.second);
                auto uni = glGetUniformLocation(this->shader->ID, item.first.c_str());
                glUniformMatrix4fv(uni, 1, GL_FALSE, &value[0][0]);
            }
            if(std::holds_alternative<Texture*>(item.second)) {
                auto value = std::get<Texture*>(item.second);
                auto texUni = glGetUniformLocation(this->shader->ID, item.first.c_str());
                glUniform1i(texUni, (GLint)value->unit);
                value->Bind();
            }
        }

    }

    void UnActivate() {

    }
};


#endif //LEARN_OPENGL_MATERIAL_H
