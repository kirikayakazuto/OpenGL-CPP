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
    glm::vec3 color;
    glm::vec2 uv;
};

class Mesh {

private:
    bool dirty;

    GLuint VAO_ID{};
    GLuint VBO_ID{};
    GLuint EBO_ID{};

public:
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    std::vector<AttributeFormat> attribute_info;

    Mesh(std::vector<AttributeFormat>& attribute_data, std::vector<float>& v_data, std::vector<GLuint>& i_data);

    GLuint GetVaoId();

    void Upload();

};


#endif //LEARN_OPENGL_MESH_H
