#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.hpp"
#include "Shader.hpp"
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const int SEGMENTS = 32;

static float vertices[(SEGMENTS + 2) * 3];
static unsigned int indices[SEGMENTS * 3];


static void GenerateCircle()
{
    float radius = 1.0f;

    // Center point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int i = 0; i <= SEGMENTS; i++)
    {
        float angle =
            (float)i / SEGMENTS *
            2.0f * 3.1415926f;

        vertices[(i + 1) * 3 + 0] = cosf(angle) * radius;
        vertices[(i + 1) * 3 + 1] = 0.0f;
        vertices[(i + 1) * 3 + 2] = sinf(angle) * radius;
    }

    for (int i = 0; i < SEGMENTS; i++)
    {
        indices[i * 3 + 0] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i + 2;
    }
}


void Renderer::Init(Shader* s, Shader* trailS)
{
    shader = s;
    trailShader = trailS;

    //glEnable(GL_DEPTH_TEST);

    // Perspective projection
    projection = glm::perspective(
        glm::radians(50.0f),
        1280.0f / 720.0f,
        0.1f,
        1000.0f
    );

    // Temporary fixed camera
    view = glm::lookAt(
        glm::vec3(0.0f, 80.0f, 100.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    GenerateCircle();

    // Circle VAO/VBO/EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    // (vec3)
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    // Trail VAO/VBO
    glGenVertexArrays(1, &trailVAO);
    glGenBuffers(1, &trailVBO);

    glBindVertexArray(trailVAO);

    glBindBuffer(GL_ARRAY_BUFFER, trailVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        2000 * 3 * sizeof(float),
        nullptr,
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void Renderer::DrawBody(const Body& body)
{
    shader->Use();

    // identity matrix
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            body.position.x,
            0.0f,
            body.position.y
        )
    );

    model = glm::scale(
        model,
        glm::vec3(body.radius)
    );

    shader->SetMat4("uModel", model);
    shader->SetMat4("uView", view);
    shader->SetMat4("uProjection", projection);

    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,
        SEGMENTS * 3,
        GL_UNSIGNED_INT,
        0
    );

    glBindVertexArray(0);
}


void Renderer::DrawTrail(const Body& body)
{
    if (body.trail.size() < 2)
        return;

    std::vector<float> points;

    for (const Vec2& p : body.trail)
    {
        points.push_back(p.x);
        points.push_back(0.0f);
        points.push_back(p.y);
    }

    glBindBuffer(GL_ARRAY_BUFFER, trailVBO);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        points.size() * sizeof(float),
        points.data()
    );

    trailShader->Use();

    trailShader->SetMat4("uView", view);
    trailShader->SetMat4("uProjection", projection);

    glBindVertexArray(trailVAO);

    glLineWidth(3.0f);

    glDrawArrays(
        GL_LINE_STRIP,
        0,
        (GLsizei)body.trail.size()
    );

    glBindVertexArray(0);
}