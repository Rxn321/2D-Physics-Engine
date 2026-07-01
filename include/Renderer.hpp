#pragma once

class Shader;

#include "Body.hpp"

class Renderer
{
public:
    void Init(Shader* shader);
    void DrawBody(const Body& body);

private:
    unsigned int VAO, VBO, EBO;
    Shader* shader;
};