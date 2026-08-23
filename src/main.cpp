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
#include "SolarSystem.hpp"

constexpr float WORLD_WIDTH  = 100.0f;
constexpr float WORLD_HEIGHT = 75.0f;

std::string LoadFile(const std::string& path)
{
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
// interactive clikc
Vec2 ScreenToWorld(double mouseX, double mouseY, int windowWidth, int windowHeight)
{
    float nx = (float)(mouseX / windowWidth);
    float ny = (float)(mouseY / windowHeight);

    // convert to world
    float worldX = (nx * 2.0f - 1.0f) * WORLD_WIDTH;
    float worldY = (1.0f - ny * 2.0f) * WORLD_HEIGHT;

    return Vec2(worldX, worldY);
}

struct AppState
{
    PhysicsWorld* world;
    int width, height;
};

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        AppState* state = (AppState*)glfwGetWindowUserPointer(window);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        Vec2 worldPos = ScreenToWorld(mouseX, mouseY, state->width, state->height);

        Body* b = new Body();

        b->position = worldPos;
        b->radius = 1.0f;
        b->mass = b->radius * 10.0f;
        b->velocity = Vec2(10.0f, 0.0f);

        state->world->AddBody(b);
    }
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
    
    std::string circleVert = LoadFile("shaders/circle.vert");
    std::string circleFrag = LoadFile("shaders/circle.frag");
    std::string trailVert = LoadFile("shaders/trail.vert");
    std::string trailFrag = LoadFile("shaders/trail.frag");

    Shader circleShader(
        circleVert,
        circleFrag
    );

    Shader trailShader(
        trailVert,
        trailFrag
    );

    Renderer renderer;
    renderer.Init(&circleShader, &trailShader);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(-8.0f, 8.0f);   // spawn x range
    std::uniform_real_distribution<float> posY(3.0f, 6.0f);    // spawn y range (near top)
    std::uniform_real_distribution<float> radiusDist(0.5f, 1.5f); // vary size

    PhysicsWorld physicsWorld;
    SolarSystem::Create(physicsWorld);
    
    AppState state;
    state.world = &physicsWorld;
    state.width = 800;
    state.height = 600;

    glfwSetWindowUserPointer(window, &state);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);

    float lastTime = glfwGetTime();
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
        
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        dt = std::min(dt, 0.033f);

        physicsWorld.Update(dt);

        for (Body* b : physicsWorld.bodies)
        {
            renderer.DrawTrail(*b);
            renderer.DrawBody(*b);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}