#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Shader.hpp"
#include <cmath>


static const int SEGMENTS = 32;

static float vertices[(SEGMENTS + 2) * 2];
static unsigned int indices[SEGMENTS * 3];


static void MakeOrtho(float* mat, float left, float right, float bottom, float top)
{
    for (int i = 0; i < 16; i++) mat[i] = 0.0f;

    mat[0] = 2.0f / (right - left);
    mat[5] = 2.0f / (top - bottom);
    mat[10] = -1.0f;
    mat[12] = -(right + left) / (right - left);
    mat[13] = -(top + bottom) / (top - bottom);
    mat[15] = 1.0f;
}

static void GenerateCircle()
{
    float radius = 1.0f;

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


void Renderer::Init(Shader* s)
{
    shader = s;
    MakeOrtho(projection, -10.0f, 10.0f, -7.5f, 7.5f);

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
    shader->SetFloat("uScale", body.radius);
    shader->SetMat4("uProjection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, SEGMENTS * 3, GL_UNSIGNED_INT, 0);
}