#pragma once
#include "Body.hpp"


class Shader;

class Renderer
{
public:
    void Init(Shader* shader, float aspectRatio);
    void DrawBody(const Body& body);

private:
    unsigned int VAO, VBO, EBO;
    Shader* shader;
    float aspect;
};