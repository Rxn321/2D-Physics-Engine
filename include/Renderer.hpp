#pragma once

#include "Body.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>
#include <vector>

class Renderer
{
public:
    void Init(Shader* shader, Shader* trailShader, Shader* sphereShader);

    void DrawBody(const Body& body);
    void DrawTrail(const Body& body);

    void GenerateSphere();
    void GenerateGravityMesh();
    void DrawGravityMesh();
    
    void UpdateGravityMesh(
        const std::vector<Body*>& bodies,
        float gravitationalConstant
    );

private:
    unsigned int VAO, VBO, EBO;
    unsigned int trailVAO, trailVBO;

    unsigned int sphereVAO, sphereVBO, sphereEBO;
    unsigned int sphereIndexCount;

    // The main char of proj
    unsigned int gravityVAO;
    unsigned int gravityVBO;
    unsigned int gravityEBO;
    unsigned int gravityIndexCount;

    Shader* shader;
    Shader* trailShader;
    Shader* sphereShader;

    glm::mat4 projection;
    glm::mat4 view;
};