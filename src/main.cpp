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
// interactive clikc
Vec2 ScreenToWorld(double mouseX, double mouseY, int windowWidth, int windowHeight)
{
    float nx = (float)(mouseX / windowWidth);
    float ny = (float)(mouseY / windowHeight);

    // convert to world
    float worldX = (nx * 2.0f - 1.0f) * 10.0f;
    float worldY = (1.0f - ny * 2.0f) * 7.5f;

    return Vec2(worldX, worldY);
}

struct AppState
{
    std::vector<Body>* bodyList;
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

        Body b;
        b.position = worldPos;
        b.radius = 1.0f;
        b.mass = b.radius * 10.0f;

        state->bodyList->push_back(b);
        state->world->AddBody(&state->bodyList->back());
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
    
    std::string vertexSrc = LoadFile("shaders/circle.vert");
    std::string fragmentSrc = LoadFile("shaders/circle.frag");
    
    Shader shader(vertexSrc, fragmentSrc);
    Renderer renderer;
    renderer.Init(&shader);

    PhysicsWorld physicsWorld;

    
    Body* sun = new Body();

    sun->position = Vec2(0,0);
    sun->mass = 1000;
    sun->radius = 2;


    Body* planet = new Body();

    planet->position = Vec2(10,0);
    planet->mass = 10;
    planet->velocity = Vec2(0,50);
    planet->radius = 0.5; 

    physicsWorld.AddBody(sun);
    physicsWorld.AddBody(planet);


    std::random_device rd;
    std::mt19937 gen(rd());
/*
    std::uniform_real_distribution<float> posX(-8.0f, 8.0f);   // spawn x range
    std::uniform_real_distribution<float> posY(3.0f, 6.0f);    // spawn y range (near top)
    std::uniform_real_distribution<float> radiusDist(0.5f, 1.5f); // vary size

    std::vector<Body> bodyList;
    bodyList.reserve(67);

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
*/

    AppState state;
//    state.bodyList = &bodyList;
    state.world = &physicsWorld;
    state.width = 1600;
    state.height = 1200;

    glfwSetWindowUserPointer(window, &state);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);

    float lastTime = glfwGetTime();
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
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