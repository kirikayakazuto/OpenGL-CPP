//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H

// #define STB_IMAGE_IMPLEMENTATION // 只需在一个源文件中定义这个宏
#include <glad/glad.h>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include "Shader.h"


class Texture {
public:
    GLuint ID{};
    const char* type;
    GLuint unit;

    Texture(const char* image, const char* texType, GLuint slot);

    // void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};


#endif //LEARN_OPENGL_TEXTURE_H
