//
// Created by 邓朗 on 2024/1/16.
//

#ifndef LEARN_OPENGL_MODEL_H
#define LEARN_OPENGL_MODEL_H

#include "./MeshRenderer.h"
#include "../materials/PBRMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model: public MeshRenderer {
private:
    // 路径地址
    std::string fileUrl;
    std::string directory;
    std::vector<Texture> textures_loaded;

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
            this->ProcessMesh(mesh, scene);
        }
        for (int i = 0; i < node->mNumChildren; ++i) {
            this->ProcessNode(node->mChildren[i], scene);
        }
    }

    void ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        for (int i = 0; i < mesh->mNumVertices; ++i) {
            Vertex vertex{};
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
//                glm::vec3 tangent;
//                tangent.x = mesh->mTangents[i].x;
//                tangent.y = mesh->mTangents[i].y;
//                tangent.z = mesh->mTangents[i].z;
//                vertex.tangent = tangent;
//                glm::vec3 bitangent;
//                bitangent.x = mesh->mBitangents[i].x;
//                bitangent.y = mesh->mBitangents[i].y;
//                bitangent.z = mesh->mBitangents[i].z;
//                vertex.bitangent = bitangent;
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

        auto m = scene->mMaterials[mesh->mMaterialIndex];
        std::unordered_map<std::string, std::vector<std::string>> textureMap;

        auto diffuseTextures = this->LoadTextures(m, aiTextureType_DIFFUSE);
        textureMap.insert(std::pair<std::string, std::vector<std::string>>("texture_diffuse", diffuseTextures));

//        auto specularTextures = this->LoadTextures(m, aiTextureType_SPECULAR);
//        textureMap.insert(std::pair<std::string, std::vector<std::string>>("texture_specular", specularTextures));
//
//        auto heightTextures = this->LoadTextures(m, aiTextureType_HEIGHT);
//        textureMap.insert(std::pair<std::string, std::vector<std::string>>("texture_normal", heightTextures));
//
//        auto ambientTextures = this->LoadTextures(m, aiTextureType_AMBIENT);
//        textureMap.insert(std::pair<std::string, std::vector<std::string>>("texture_height", ambientTextures));

        this->meshes.emplace_back(attribute, vertices, indices);
        this->materials.push_back(PBRMaterial(textureMap));
    }

    std::vector<std::string> LoadTextures(aiMaterial* aiMaterial, aiTextureType type) {
        std::vector<std::string> textures;
        for(unsigned int i = 0; i < aiMaterial->GetTextureCount(type); i++) {
            aiString str;
            aiMaterial->GetTexture(type, i, &str);
            // std::cout << str.C_Str() << std::endl;
            textures.emplace_back(str.C_Str());
        }
        return textures;
    }

//    void LoadTextures(aiMaterial* aiMaterial, aiTextureType type) {
//        std::vector<Texture> textures;
//        for(unsigned int i = 0; i < aiMaterial->GetTextureCount(type); i++)
//        {
//            aiString str;
//            aiMaterial->GetTexture(type, i, &str);
//            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//            bool skip = false;
//            for(unsigned int j = 0; j < textures_loaded.size(); j++) {
//                if(std::strcmp(textures_loaded[j].url.data(), str.C_Str()) == 0) {
//                    textures.push_back(textures_loaded[j]);
//                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
//                    break;
//                }
//            }
//            if(!skip) {   // if texture hasn't been loaded already, load it
//                Texture texture("", 0);
//                textures.push_back(texture);
//                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
//            }
//        }
//        return textures;
//    }
public:

    std::unordered_map<std::string, Texture*> textures;

    Model(): MeshRenderer() {
        std::string url = "assets/models/man/nanosuit.obj";
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
    }
};

#endif //LEARN_OPENGL_MODEL_H
