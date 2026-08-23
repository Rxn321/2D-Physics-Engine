#pragma once

#include "Body.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

class Renderer
{
public:
    void Init(Shader* shader, Shader* trailShader);

    void DrawBody(const Body& body);
    void DrawTrail(const Body& body);

private:
    unsigned int VAO, VBO, EBO;
    unsigned int trailVAO, trailVBO;

    Shader* shader;
    Shader* trailShader;

    glm::mat4 projection;
    glm::mat4 view;
};