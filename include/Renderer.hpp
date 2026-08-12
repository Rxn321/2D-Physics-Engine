#pragma once
#include "Body.hpp"
#include "Shader.hpp"


class Shader;

class Renderer
{
public:
    void Init(Shader* shader, Shader* trailShader);
    void DrawBody(const Body& body);
    void DrawTrail(const Body& body);

private:
    unsigned int VAO, VBO, EBO;
    unsigned int trailVAO,  trailVBO;
    Shader* shader;
    Shader* trailShader;
    float projection[16];
};