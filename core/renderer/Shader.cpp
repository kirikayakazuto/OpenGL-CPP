//
// Created by 邓朗 on 2024/1/6.
//

#include "Shader.h"

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
    auto vertStr = this->GetFileContent(vertexFile);
    auto fragStr = this->GetFileContent(fragmentFile);

    auto vertSource = vertStr.c_str();
    auto fragSource = fragStr.c_str();

    auto vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, nullptr);
    glCompileShader(vertShader);
    this->CompileShader(vertShader, "VERTEX");

    auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, nullptr);
    glCompileShader(fragShader);
    this->CompileShader(fragShader, "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertShader);
    glAttachShader(this->ID, fragShader);
    glLinkProgram(this->ID);
    this->CompileProgram(this->ID);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

std::string Shader::GetFileContent(const char *filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

void Shader::CompileShader(unsigned int shader, const char* type) {
    GLint hasCompiled;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
    }
}

void Shader::CompileProgram(unsigned int program) {
    GLint hasCompiled;
    char infoLog[1024];

    glGetProgramiv(program, GL_LINK_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "SHADER_LINKING_ERROR for \n" << infoLog << std::endl;
    }
}

void Shader::Activate() {
    glUseProgram(this->ID);
}

void Shader::Delete() {
    glDeleteProgram(this->ID);
}




