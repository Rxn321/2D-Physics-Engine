#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include <iostream>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        char log[512];
        glGetProgramInfoLog(ID, 512, nullptr, log);
        std::cout << "Program Link Error:\n" << log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& src)
{
    unsigned int shader = glCreateShader(type);

    const char* csrc = src.c_str();
    glShaderSource(shader, 1, &csrc, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cout << "Shader Compile Error:\n" << log << std::endl;
    }

    return shader;
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetVec2(const std::string& name, float x, float y)
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc != -1)
        glUniform2f(loc, x, y);
}