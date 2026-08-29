#pragma once

#include "Body.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

class Renderer
{
public:
    void Init(Shader* shader, Shader* trailShader, Shader* sphereShader);

    void DrawBody(const Body& body);
    void DrawTrail(const Body& body);
    void GenerateSphere();

private:
    unsigned int VAO, VBO, EBO;
    unsigned int trailVAO, trailVBO;

    unsigned int sphereVAO, sphereVBO, sphereEBO;
    unsigned int sphereIndexCount;

    Shader* shader;
    Shader* trailShader;
    Shader* sphereShader;

    glm::mat4 projection;
    glm::mat4 view;
};