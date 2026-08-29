#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int ID;

    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

    void Use();

    void SetVec2(const std::string& name, float x, float y);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetFloat(const std::string& name, float value);

    void SetMat4(const std::string& name, const glm::mat4& mat);

private:
    unsigned int CompileShader(unsigned int type, const std::string& src);
};