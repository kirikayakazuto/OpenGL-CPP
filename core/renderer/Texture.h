//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H

// #define STB_IMAGE_IMPLEMENTATION // 只需在一个源文件中定义这个宏
#include <glad/glad.h>
#include <FreeImage.h>
#include <iostream>


class Texture {
public:
    std::string url;
    GLuint ID{};
    GLuint unit;

    Texture(const std::string& url, GLuint slot) {
        this->url = url;
        auto image = url.c_str();
        FreeImage_Initialise();

        FIBITMAP* imageBitmap = nullptr;
        FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(image, 0);
        if (imageFormat == FIF_UNKNOWN) {
            imageFormat = FreeImage_GetFIFFromFilename(image);
        }
        if (imageFormat != FIF_UNKNOWN && FreeImage_FIFSupportsReading(imageFormat)) {
            imageBitmap = FreeImage_Load(imageFormat, image);
        }

        if (imageBitmap) {
            auto widthImg = (int)FreeImage_GetWidth(imageBitmap);
            auto heightImg = (int)FreeImage_GetHeight(imageBitmap);
            std::cout << widthImg << " x " << heightImg << std::endl;

            GLubyte* bytes = FreeImage_GetBits(imageBitmap);

            glGenTextures(1, &this->ID);
            glActiveTexture(GL_TEXTURE0 + slot);
            this->unit = slot;
            glBindTexture(GL_TEXTURE_2D, this->ID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            const auto format = FreeImage_GetBPP(imageBitmap) == 32 ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format == GL_RGBA ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, (void*)bytes);
            glGenerateMipmap(GL_TEXTURE_2D);

            FreeImage_Unload(imageBitmap);
        } else {
            std::cout << url << " :load error" << std::endl;
        }

        FreeImage_DeInitialise();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind() const {
        glActiveTexture(GL_TEXTURE0 + this->unit);
        glBindTexture(GL_TEXTURE_2D, this->ID);
    }
    static void Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    void Delete() {
        glDeleteTextures(1, &this->ID);
    }
};


#endif //LEARN_OPENGL_TEXTURE_H
