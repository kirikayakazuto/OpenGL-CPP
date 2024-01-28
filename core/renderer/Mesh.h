//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_MESH_H
#define LEARN_OPENGL_MESH_H

#include <glad/glad.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <GLFW/glfw3.h>
#include <iostream>


struct AttributeFormat {
    std::string name;
    unsigned int num;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh {

private:
    bool dirty;

    GLuint VAO_ID{};
    GLuint VBO_ID{};
    GLuint EBO_ID{};

    static unsigned int GetAttributeNums(std::vector<AttributeFormat>& attribute_info) {
        unsigned int total = 0;
        for (const auto& attribute : attribute_info) {
            total += attribute.num;
        }
        return total;
    }

public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<AttributeFormat> attribute_info;

    Mesh(std::vector<AttributeFormat>& attribute_data, std::vector<Vertex>& v_data, std::vector<GLuint>& i_data)
            : attribute_info(attribute_data),
              vertices(v_data),
              indices(i_data) {

        this->dirty = true;

        // VAO
        glGenVertexArrays(1, &this->VAO_ID);
        glBindVertexArray(this->VAO_ID);

        // VBO
        glGenBuffers(1, &this->VBO_ID);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

        // EBO
        glGenBuffers(1, &this->EBO_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);

        // link attribute
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
        unsigned int index = 0;
        auto total = Mesh::GetAttributeNums(this->attribute_info);
        std::cout << total << std::endl;
        for (size_t i=0; i<this->attribute_info.size(); ++i) {
            auto attribute = this->attribute_info[i];
            std::cout << attribute.name << attribute.num << std::endl;
            glVertexAttribPointer(i, attribute.num, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(index * sizeof(float)));
            glEnableVertexAttribArray(i);
            index += attribute.num;
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint GetVaoId() const {
        return this->VAO_ID;
    }

    void Upload() {
        if(!this->dirty) return;
        this->dirty = false;
    }

};


#endif //LEARN_OPENGL_MESH_H
