#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "PhysicsWorld.hpp"
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

static const int SEGMENTS = 32;

static float vertices[(SEGMENTS + 2) * 3];
static unsigned int indices[SEGMENTS * 3];
const float VISUAL_G = 10.0f;


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


void Renderer::Init(Shader* s, Shader* trailS, Shader* sphereS)
{
    shader = s;
    trailShader = trailS;
    sphereShader = sphereS;

    glEnable(GL_DEPTH_TEST);

    // Perspective projection
    projection = glm::perspective(
        glm::radians(50.0f),
        800.0f / 600.0f,
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
    GenerateSphere();
    GenerateGravityMesh();
    

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
    sphereShader->Use();

    // Calculate visual size from mass
    float visualRadius = std::cbrt(body.mass) * 0.5f;

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
        glm::vec3(visualRadius)
    );

    sphereShader->SetMat4("model", model);
    sphereShader->SetMat4("view", view);
    sphereShader->SetMat4("projection", projection);

    sphereShader->SetVec3(
        "objectColor",
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    sphereShader->SetVec3(
        "lightPos",
        glm::vec3(0.0f, 80.0f, 100.0f)
    );

    glBindVertexArray(sphereVAO);

    glDrawElements(
        GL_TRIANGLES,
        sphereIndexCount,
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

    glLineWidth(1.0f);

    glDrawArrays(
        GL_LINE_STRIP,
        0,
        (GLsizei)body.trail.size()
    );

    glBindVertexArray(0);
}

void Renderer::GenerateSphere()
{
    const int STACKS = 16;
    const int SECTORS = 32;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= STACKS; i++)
    {
        float phi = glm::pi<float>() * i / STACKS;

        for (int j = 0; j <= SECTORS; j++)
        {
            float theta = 2.0f * glm::pi<float>() * j / SECTORS;

            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Normal
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    for (int i = 0; i < STACKS; i++)
    {
        for (int j = 0; j < SECTORS; j++)
        {
            int current = i * (SECTORS + 1) + j;
            int next = current + SECTORS + 1;

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);

            indices.push_back(current + 1);
            indices.push_back(next);
            indices.push_back(next + 1);
        }
    }

    sphereIndexCount = indices.size();

    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);

    glBindVertexArray(sphereVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    std::cout << "Sphere generated: "
          << sphereIndexCount
          << " indices\n";
    
}

void Renderer::GenerateGravityMesh()
{
    const int GRID_SIZE = 150;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float spacingX = WORLD_WIDTH / (GRID_SIZE - 1);
    float spacingZ = WORLD_HEIGHT / (GRID_SIZE - 1);

    // Generate vertices
    for (int z = 0; z < GRID_SIZE; z++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            float worldX =
                -WORLD_WIDTH / 2.0f + x * spacingX;

            float worldZ =
                -WORLD_HEIGHT / 2.0f + z * spacingZ;

            vertices.push_back(worldX);
            vertices.push_back(0.0f);
            vertices.push_back(worldZ);
        }
    }

    // Horizontal lines
    for (int z = 0; z < GRID_SIZE; z++)
    {
        for (int x = 0; x < GRID_SIZE - 1; x++)
        {
            unsigned int current =
                z * GRID_SIZE + x;

            indices.push_back(current);
            indices.push_back(current + 1);
        }
    }

    // Vertical lines
    for (int z = 0; z < GRID_SIZE - 1; z++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            unsigned int current =
                z * GRID_SIZE + x;

            indices.push_back(current);
            indices.push_back(current + GRID_SIZE);
        }
    }

    gravityIndexCount =
        static_cast<unsigned int>(indices.size());

    glGenVertexArrays(1, &gravityVAO);
    glGenBuffers(1, &gravityVBO);
    glGenBuffers(1, &gravityEBO);

    glBindVertexArray(gravityVAO);

    glBindBuffer(GL_ARRAY_BUFFER, gravityVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_DYNAMIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gravityEBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
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

    std::cout << "Gravity indices: "
              << gravityIndexCount
              << std::endl;
}

void Renderer::DrawGravityMesh()
{
    glm::mat4 model = glm::mat4(1.0f);

    sphereShader->Use();

    sphereShader->SetMat4("model", model);
    sphereShader->SetMat4("view", view);
    sphereShader->SetMat4("projection", projection);

    sphereShader->SetVec3(
        "objectColor",
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    sphereShader->SetVec3(
        "lightPos",
        glm::vec3(0.0f, 80.0f, 100.0f)
    );

    glBindVertexArray(gravityVAO);

    glDisable(GL_CULL_FACE);

    glDrawElements(
        GL_LINES,
        gravityIndexCount,
        GL_UNSIGNED_INT,
        0
    );

    glBindVertexArray(0);
}

void Renderer::UpdateGravityMesh(
    const std::vector<Body*>& bodies,
    float gravitationalConstant)
{
    const int GRID_SIZE = 150;

    const float VISUAL_SCALE = 0.01f;
    const float MIN_DISTANCE = 1.0f;

    std::vector<float> vertices;

    float spacingX =
        WORLD_WIDTH / (GRID_SIZE - 1);

    float spacingZ =
        WORLD_HEIGHT / (GRID_SIZE - 1);

    for (int z = 0; z < GRID_SIZE; z++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            float worldX =
                -WORLD_WIDTH / 2.0f + x * spacingX;

            float worldZ =
                -WORLD_HEIGHT / 2.0f + z * spacingZ;

            float height = 0.0f;

            for (const Body* body : bodies)
            {
                float dx =
                    worldX - body->position.x;

                float dz =
                    worldZ - body->position.y;

                float distance =
                    std::sqrt(dx * dx + dz * dz);

                distance =
                    std::max(distance, MIN_DISTANCE);

                height -=
                    (gravitationalConstant *
                     body->mass /
                     distance) *
                    VISUAL_SCALE;
            }

            vertices.push_back(worldX);
            vertices.push_back(height);
            vertices.push_back(worldZ);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, gravityVBO);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        vertices.size() * sizeof(float),
        vertices.data()
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}