#include <iostream>

#include "core/renderer/Renderer.h"
#include "core/scene/Node.h"


GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
        0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
        0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
    };

// Indices for vertices order
GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2 // Lower triangle
    };


int main() {
    // 初始化 renderer
    std::unique_ptr<Renderer> renderer(new Renderer());
    renderer->init(800, 600);
    renderer->main_loop();


//    std::vector<AttributeFormat> attribute = {{ "a_position", 3 }, { "a_position", 3 }};
//    std::vector<Vertex> vertexs = {};
//    std::vector<GLuint> indexs = {};
//    std::unique_ptr<Mesh> mesh(new Mesh(attribute, vertexs, indexs));
//
//    auto shader = new Shader("./test/shaders/default.vert", "./test/shaders/default.frag");
//    std::unique_ptr<Material> material(new Material(*shader));
//
//    std::unique_ptr<Node> node(new Node("Root", *mesh, *material));
//
//    node->SetPosition(glm::vec3(0, 0, 0));
//    node->SetScale(glm::vec3(1, 1, 1));


    // std::unique_ptr<Material> material(new Material());


    return 0;
}