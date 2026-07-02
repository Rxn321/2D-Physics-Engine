#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

#include "Renderer.hpp"
#include "Body.hpp"
#include "Shader.hpp"
#include "PhysicsWorld.hpp"

std::string LoadFile(const std::string& path)
{
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Physics Engine", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    std::string vertexSrc = LoadFile("../shaders/circle.vert");
    std::string fragmentSrc = LoadFile("../shaders/circle.frag");

    Shader shader(vertexSrc, fragmentSrc);
    Renderer renderer;
    renderer.Init(&shader, 800.0f / 600.0f);

    PhysicsWorld physicsWorld;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(-0.8f, 0.8f);   // spawn x range
    std::uniform_real_distribution<float> posY(0.5f, 0.9f);    // spawn y range (near top)
    std::uniform_real_distribution<float> radiusDist(0.05f, 0.15f); // vary size

    std::vector<Body> bodyList;
    bodyList.reserve(5);

    for (int i = 0; i < 5; i++)
    {
        Body b;
        b.position = Vec2(posX(gen), posY(gen));
        b.radius = radiusDist(gen);
        b.mass = b.radius * 10.0f;
        bodyList.push_back(b);
    }



    for (Body& b : bodyList)
    {
        physicsWorld.AddBody(&b); // pointers
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        physicsWorld.Update(0.016f);

        for (Body* b : physicsWorld.bodies)
        {
            renderer.DrawBody(*b);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}