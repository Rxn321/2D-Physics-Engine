#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Shader.hpp"
#include <cmath>


static const int SEGMENTS = 32;

static float vertices[(SEGMENTS + 2) * 2];
static unsigned int indices[SEGMENTS * 3];


static void GenerateCircle()
{
    float radius = 0.1f;

    // center point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    for (int i = 0; i <= SEGMENTS; i++)
    {
        float angle = (float)i / SEGMENTS * 2.0f * 3.1415926f;

        vertices[(i + 1) * 2 + 0] = cosf(angle) * radius;
        vertices[(i + 1) * 2 + 1] = sinf(angle) * radius;
    }

    for (int i = 0; i < SEGMENTS; i++)
    {
        indices[i * 3 + 0] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i + 2;
    }
}


void Renderer::Init(Shader* s, float aspectRatio)
{
    shader = s;
    aspect = aspectRatio;

    GenerateCircle();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute (vec2)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void Renderer::DrawBody(const Body& body)
{
    shader->Use();
    shader->SetVec2("uPos", body.position.x, body.position.y);
    shader->SetFloat("uScale", body.radius / 0.1f);
    shader->SetFloat("uAspect", aspect);

    // send position to GPU
    shader->SetVec2("uPos", body.position.x, body.position.y);

    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,
        SEGMENTS * 3,
        GL_UNSIGNED_INT,
        0
    );
}