//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H

// #define STB_IMAGE_IMPLEMENTATION // 只需在一个源文件中定义这个宏
#include <glad/glad.h>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include <iostream>


class Texture {
public:
    GLuint ID{};
    GLuint unit;

    Texture(const std::string& url, GLuint slot);

    // void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind() const;
    static void Unbind();
    void Delete();
};


#endif //LEARN_OPENGL_TEXTURE_H
