//
// Created by 邓朗 on 2024/1/16.
//

#ifndef LEARN_OPENGL_MODEL_H
#define LEARN_OPENGL_MODEL_H

#include "./MeshRenderer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model: public MeshRenderer{
private:
    // 路径地址
    std::string fileUrl;
    std::vector<Mesh> meshes;
    std::string directory;

    void LoadMesh() {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(this->fileUrl, aiProcess_Triangulate | aiProcess_FlipUVs);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR: Assimp::" << importer.GetErrorString() << std::endl;
            return;
        }
        this->ProcessNode(scene->mRootNode, scene);
    }

    void ProcessNode(aiNode* node, const aiScene* scene) {
        for (int i = 0; i < node->mNumMeshes; ++i) {
            auto mesh = scene->mMeshes[node->mMeshes[i]];
            this->meshes.push_back(this->ProcessMesh(mesh, scene));
        }
        for (int i = 0; i < node->mNumChildren; ++i) {
            this->ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        for (int i = 0; i < mesh->mNumVertices; ++i) {
            Vertex vertex;
            glm::vec3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;
            vertex.position = position;
            if(mesh->HasNormals()) {
                glm::vec3 normal;
                normal.x = mesh->mNormals[i].x;
                normal.y = mesh->mNormals[i].y;
                normal.z = mesh->mNormals[i].z;
                vertex.normal = normal;
            }
            if(mesh->mTextureCoords[0]) {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.uv = vec;
                glm::vec3 tangent;
                tangent.x = mesh->mTangents[i].x;
                tangent.y = mesh->mTangents[i].y;
                tangent.z = mesh->mTangents[i].z;
                vertex.tangent = tangent;
                glm::vec3 bitangent;
                bitangent.x = mesh->mBitangents[i].x;
                bitangent.y = mesh->mBitangents[i].y;
                bitangent.z = mesh->mBitangents[i].z;
                vertex.bitangent = bitangent;
            } else {
                vertex.uv = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }
        for (int i = 0; i < mesh->mNumFaces; ++i) {
            auto face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }
        std::vector<AttributeFormat> attribute = {
                { "a_position", 3 },
                {"a_normal", 3},
                {"a_uv", 2},
                {"a_tangent", 3},
                {"a_bitangent", 3}
        };
        return Mesh(attribute, vertices, indices);
    }
public:

    std::unordered_map<std::string, Texture*> textures;

    Model(std::string& url) {
        this->fileUrl = url;
        this->directory = url.substr(0, url.find_last_of('/'));
        std::vector<AttributeFormat> attribute = {
                { "a_position", 3 },
                {"a_normal", 3},
                {"a_uv", 2},
                {"a_tangent", 3},
                {"a_bitangent", 3}
        };
        this->LoadMesh();
        this->mesh = new Mesh(attribute, this->vertices, this->indices);
    }

};

#endif //LEARN_OPENGL_MODEL_H
