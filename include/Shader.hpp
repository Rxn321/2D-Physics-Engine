#pragma once

#include <string>
#include <glad/glad.h>

class Shader
{
public:
    unsigned int ID;

    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

    void Use();
    void SetVec2(const std::string& name, float x, float y);

private:
    unsigned int CompileShader(unsigned int type, const std::string& src);
};