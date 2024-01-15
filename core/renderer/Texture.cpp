//
// Created by 邓朗 on 2024/1/6.
//

#include "Texture.h"

Texture::Texture(const std::string& url, GLuint slot) {
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
        auto widthImg = FreeImage_GetWidth(imageBitmap);
        auto heightImg = FreeImage_GetHeight(imageBitmap);
        std::cout << widthImg << " X " << heightImg << std::endl;

        GLubyte* bytes = FreeImage_GetBits(imageBitmap);

        glGenTextures(1, &this->ID);
        glActiveTexture(GL_TEXTURE0 + slot);
        this->unit = slot;
        glBindTexture(GL_TEXTURE_2D, this->ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        GLenum format = FreeImage_GetBPP(imageBitmap) == 32 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)bytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        FreeImage_Unload(imageBitmap);
    }

     FreeImage_DeInitialise();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const {
    glActiveTexture(GL_TEXTURE0 + this->unit);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &this->ID);
}
