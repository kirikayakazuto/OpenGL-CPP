//
// Created by 邓朗 on 2024/1/16.
//

#ifndef LEARN_OPENGL_MODEL_H
#define LEARN_OPENGL_MODEL_H

#include <nlohmann/json.hpp>
#include "../renderer/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../renderer/Texture.h"

class Model {
private:
    // 路径地址
    std::string fileUrl;
    // 模型json数据
    nlohmann::json modelJson;
    // 模型的mesh buffer
    std::vector<unsigned char> meshBuffer;
    // mesh的矩阵变换
    std::vector<glm::mat4> matricesMeshes;

    static std::string GetFileContent(const char* filename) {
        std::ifstream in(filename, std::ios::binary);
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], (long)contents.size());
            in.close();
            return(contents);
        }
        throw("get file content error");
    }

    void GetModelData(const char* url) {
        this->modelJson = nlohmann::json::parse(Model::GetFileContent(url));
        std::string bytesText;
        std::string uri = modelJson["buffers"][0]["uri"];

        std::string fileStr = std::string(url);
        std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);
        bytesText = Model::GetFileContent((fileDir + uri).c_str());

        this->meshBuffer = std::vector<unsigned char>(bytesText.begin(), bytesText.end());

        this->TraverseNode(0, glm::mat4(1.0f));
    }

    void TraverseNode(unsigned int next, glm::mat4 matrix) {
         auto node = this->modelJson["nodes"][next];


         glm::vec3 translation = glm::vec3(1.0f, 1.0f, 1.0f);
         // 计算translation
         if(node.find("translation") != node.end()) {
             float transValues[3];
            for(unsigned int i=0; i<3; i++) {
                transValues[i] = node["translation"][i];
            }
            translation = glm::make_vec3(transValues);
         }

         glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
         if(node.find("rotation") != node.end()) {
             float rotValues[4] = {node["rotation"][3], node["rotation"][0], node["rotation"][1], node["rotation"][2]};
             rotation = glm::make_quat(rotValues);
         }

         glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        if(node.find("scale") != node.end()) {
            float scaleValues[3];
            for(unsigned int i=0; i<3; i++) {
                scaleValues[i] = node["scale"][i];
            }
            scale = glm::make_vec3(scaleValues);
        }

        glm::mat4 matNode = glm::mat4(1.0f);
        if (node.find("matrix") != node.end()) {
            float matValues[16];
            for (unsigned int i = 0; i < node["matrix"].size(); i++) {
                matValues[i] = (node["matrix"][i]);
            }
            matNode = glm::make_mat4(matValues);
        }

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        trans = glm::translate(trans, translation);
        rot = glm::mat4_cast(rotation);
        sca = glm::scale(sca, scale);

        glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

        if(node.find("mesh") != node.end()) {
            this->matricesMeshes.push_back(matNextNode);
        }

        if(node.find("children") != node.end()) {
            for (const auto & i : node["children"]) {
                this->TraverseNode(i, matNextNode);
            }
        }
    }

    void LoadMesh(unsigned int meshIndex) {
        auto meshJson = this->modelJson["meshes"][meshIndex]["primitives"][0];

        auto positionVec = this->GetFloats(this->modelJson["accessors"][meshJson["POSITION"]]);
        auto normalVec = this->GetFloats(this->modelJson["accessors"][meshJson["NORMAL"]]);
        auto uvVec = this->GetFloats(this->modelJson["accessors"][meshJson["TEXCOORD_0"]]);

    }

    std::vector<float> GetFloats(nlohmann::json accessor) {
        std::vector<float> floatVec;
        unsigned int buffViewIndex = accessor.value("bufferView", 1);
        unsigned int count = accessor["count"];
        unsigned int accByteOffset = accessor.value("byteOffset", 0);
        std::string type = accessor["type"];

        nlohmann::json bufferView = this->modelJson["bufferViews"][buffViewIndex];
        unsigned int byteOffset = bufferView["byteOffset"];

        unsigned int numPerVert = 0;
        if(type == "SCALAR") numPerVert = 1;
        else if(type == "VEC2") numPerVert = 2;
        else if(type == "VEC3") numPerVert = 3;
        else if(type == "VEC4") numPerVert = 4;

        unsigned int beginningOfData = byteOffset + accByteOffset;
        unsigned int lengthOfData = count * 4 * numPerVert;

        for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i) {
            unsigned char bytes[] = {this->meshBuffer[i++], this->meshBuffer[i++], this->meshBuffer[i++], this->meshBuffer[i++]};
            float value;
            std::memcpy(&value, bytes, sizeof(float));
            floatVec.push_back(value);
        }

        return floatVec;
    }

public:

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::unordered_map<std::string, Texture*> textures;

    Model(const char* url) {
        this->fileUrl = url;
        this->GetModelData(url);
    }

};

#endif //LEARN_OPENGL_MODEL_H
