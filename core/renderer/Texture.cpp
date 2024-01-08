//
// Created by 邓朗 on 2024/1/6.
//

#include "Texture.h"

Texture::Texture(const char *image, const char *texType, GLuint slot) {
    this->type = texType;
    stbi_set_flip_vertically_on_load(true);

    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &this->ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    this->unit = slot;
    glBindTexture(GL_TEXTURE_2D, this->ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    auto format = numColCh == 4 ? GL_RGBA : numColCh == 3 ? GL_RGB : GL_RED;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);

    stbi_image_free(bytes);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + this->unit);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &this->ID);
}
