//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_MATERIAL_H
#define LEARN_OPENGL_MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Material {
private:
    std::unordered_map<std::string, Texture*> textureMap;
    std::unordered_map<std::string, double> doubleMap;
    std::unordered_map<std::string, const float*> matMap;
public:
    Shader* shader;

    Material(Shader* shader);

    void SetTexture(std::string key, Texture* val);

    void SetUniformMat(std::string key, const float* val);

    void Activate();
};


#endif //LEARN_OPENGL_MATERIAL_H
