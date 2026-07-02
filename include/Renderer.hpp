#pragma once
#include "Body.hpp"
#include "Shader.hpp"


class Shader;

class Renderer
{
public:
    void Init(Shader* shader);
    void DrawBody(const Body& body);

private:
    unsigned int VAO, VBO, EBO;
    Shader* shader;
    float projection[16];
};