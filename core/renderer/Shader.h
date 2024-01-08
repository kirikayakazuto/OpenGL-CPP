//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <glad/glad.h>
#include<string>
#include <fstream>
#include <sstream>
#include<iostream>

class Shader {
private:
    std::string GetFileContent(const char* filename);
    void CompileShader(unsigned int shader, const char* type);
    void CompileProgram(unsigned int program);
public:
    GLuint ID;

    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();

    void Delete();
};


#endif //LEARN_OPENGL_SHADER_H
