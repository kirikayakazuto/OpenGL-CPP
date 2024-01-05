//
// Created by 邓朗 on 2024/1/4.
//

#ifndef LEARN_OPENGL_MESH_H
#define LEARN_OPENGL_MESH_H

#include <vector>
#include <string>

struct AttributeFormat {
    std::string name;
    unsigned int num;
};

class Mesh {
private:
    std::vector<unsigned int> indices;
    std::vector<float> vertices;
public:
    std::vector<AttributeFormat> attributeInfos;
};


#endif //LEARN_OPENGL_MESH_H
