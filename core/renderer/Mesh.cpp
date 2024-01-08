//
// Created by 邓朗 on 2024/1/4.
//

#include "Mesh.h"

unsigned int GetAttributeNums(std::unique_ptr<std::vector<AttributeFormat>>& attribute_info) {
    unsigned int total = 0;
    for (size_t i=0; i<attribute_info->size(); ++i) {
        auto attribute = (*attribute_info)[i];
        total += attribute.num;
    }
    return total;
}

Mesh::Mesh(std::vector<AttributeFormat>& attribute_data, std::vector<Vertex>& v_data, std::vector<GLuint>& i_data)
    : attribute_info(std::make_unique<std::vector<AttributeFormat>>(attribute_data)),
      vertices(std::make_unique<std::vector<Vertex>>(v_data)),
      indices(std::make_unique<std::vector<GLuint>>(i_data)) {

    this->dirty = true;

    this->vertices->data();

    // VAO
    glGenVertexArrays(1, &this->VAO_ID);
    glBindVertexArray(this->VAO_ID);

    // VBO
    glGenBuffers(1, &this->VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);

    glBufferData(GL_ARRAY_BUFFER, this->vertices->size() * sizeof(Vertex), this->vertices->data(), GL_STATIC_DRAW);

    // EBO
    glGenBuffers(1, &this->EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices->size() * sizeof(GLuint), this->indices->data(), GL_STATIC_DRAW);

    // link attribute
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
    unsigned int index = 0;
    unsigned int total = GetAttributeNums(this->attribute_info);
    for (size_t i=0; i<this->attribute_info->size(); ++i) {
        auto attribute = (*this->attribute_info.get())[i];
        glVertexAttribPointer(index, attribute.num, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)0);
        glEnableVertexAttribArray(index);
        index += attribute.num;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::Upload() {
    if(!this->dirty) return;
    this->dirty = false;
}

void Mesh::Draw() {
    glBindVertexArray(this->VAO_ID);
    glDrawElements(GL_TRIANGLES, this->indices->size(), GL_UNSIGNED_INT, 0);
}


