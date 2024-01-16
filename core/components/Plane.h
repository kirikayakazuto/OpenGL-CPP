//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_PLANE_H
#define LEARN_OPENGL_PLANE_H

#include "MeshRenderer.h"

float vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
        0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
        0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f
    };

GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };

class Plane: public MeshRenderer{
public:
    Plane(): MeshRenderer() {
        std::vector<AttributeFormat> attribute = {{ "a_position", 3 }, { "a_color", 3 }, {"a_uv", 2}};
        std::vector<float> vertice = {vertices, vertices + sizeof(vertices) / sizeof(float)};
        std::vector<GLuint> index(indices, indices + sizeof(indices) / sizeof(GLuint));
        this->mesh = new Mesh(attribute, vertice, index);
    }

    void SetMaterial(Material* m) {
        this->material = m;
    }
};


#endif //LEARN_OPENGL_PLANE_H
