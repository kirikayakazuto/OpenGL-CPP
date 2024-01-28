//
// Created by 邓朗 on 2024/1/19.
//

#ifndef LEARN_OPENGL_GLTFMODEL_H
#define LEARN_OPENGL_GLTFMODEL_H

#include <iostream>
#include <tiny_gltf.h>
#include "../renderer/Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class GltfModel {

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<glm::mat4> matrixs;

    tinygltf::Model model;

    void BindModelNode(tinygltf::Node& node, glm::mat4 matrix) {
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
        if(!node.translation.empty()) {
            translation = glm::make_vec3(node.translation.data());
        }
        auto roataion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        if(!node.rotation.empty()) {
            roataion = glm::make_quat(node.rotation.data());
        }
        auto scale = glm::vec3(1.0f, 1.0f, 1.0f);
        if(!node.scale.empty()) {
            scale = glm::make_vec3(node.scale.data());
        }
        auto currMatrix = glm::mat4(1.0f);
        if(!node.matrix.empty()) {
            currMatrix = glm::make_mat4(node.matrix.data());
        }
        auto translationMat = glm::mat4(1.0f);
        auto roataionMat = glm::mat4(1.0f);
        auto scaleMat = glm::mat4(1.0f);
        translationMat = glm::translate(translationMat, translation);
        roataionMat = glm::mat4_cast(roataion);
        scaleMat = glm::scale(scaleMat, scale);

        glm::mat4 matrixNext = matrix * currMatrix * translationMat * roataionMat * scaleMat;

        if(node.mesh != -1) {
            this->matrixs.push_back(matrixNext);
        }

        std::cout << translation.x << std::endl;

        for (const auto &childIndex: node.children) {
            this->BindModelNode(this->model.nodes[childIndex], matrixNext);
        }
    }

    void LoadMesh(unsigned int meshIndex) {
        for (const auto &bufferView: this->model.bufferViews) {
            auto buffer = this->model.buffers[bufferView.buffer];
        }
        auto mesh = this->model.meshes[meshIndex];
        for(auto & primitive : mesh.primitives) {
            auto position = primitive.attributes["POSITION"];
            auto normal = primitive.attributes["NORMAL"];
            auto uv = primitive.attributes["TEXCOORD_0"];
            auto indice = primitive.indices;

            auto positionAccessor = this->model.accessors[position];
            auto normalAccessor = this->model.accessors[normal];
            auto uvAccessor = this->model.accessors[uv];

            auto positionVec = this->GetVectors(positionAccessor);
            auto normalVec = this->GetVectors(normalAccessor);
        }

    }

    std::vector<glm::vec3> GetVectors(tinygltf::Accessor& accessor) {
        std::vector<float> floatVec;

        auto bufferView = this->model.bufferViews[accessor.bufferView];
        auto buffer = this->model.buffers[bufferView.buffer];
        int size = 1;
        if(accessor.type != TINYGLTF_TYPE_SCALAR) {
            size = accessor.type;
        }
        auto lengthOfData = accessor.count * 4 * size;

        for(auto i=0; i<lengthOfData; ) {
            unsigned char bytes[] = {buffer.data[i++], buffer.data[i++], buffer.data[i++], buffer.data[i++]};
            float value;
            std::memcpy(&value, bytes, sizeof(float ));
            floatVec.push_back(value);
        }

        std::vector<glm::vec3> vectors;
        for(int i=0; i<floatVec.size(); ) {
            auto a = i++;
            auto b = i++;
            auto c = i++;
            vectors.emplace_back(floatVec[a], floatVec[b], floatVec[c]);
        }

        return vectors;
    }

    void AssembleVertices() {

    }
public:
    GltfModel(const std::string& fileUrl) {
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;
        auto ret = loader.LoadBinaryFromFile(&this->model, &err, &warn, fileUrl.c_str());
        if(!warn.empty()) {
            std::cout << warn << std::endl;
        }
        if(!err.empty()) {
            std::cout << err << std::endl;
        }

        auto scene = this->model.scenes[this->model.defaultScene];
        for (const auto &nodeIndex: scene.nodes) {
            this->BindModelNode(this->model.nodes[nodeIndex], glm::mat4(1.0f));
        }
    }

};

#endif //LEARN_OPENGL_GLTFMODEL_H
