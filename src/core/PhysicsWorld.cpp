#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld()
{
    gravity = Vec2(0.0f, -9.8f);
}

void PhysicsWorld::AddBody(Body* body)
{
    bodies.push_back(body);
}

void PhysicsWorld::Update(float dt)
{
    for (Body* body : bodies)
    {
        body->ApplyForce(gravity * body->mass);
        body->Update(dt);

        // floor collision (NDC bottom = -1.0)
        float floorY = -1.0f + 0.1f; // account for circle radius (0.1f in NDC)
        if (body->position.y < floorY)
        {
            body->position.y = floorY;
            body->velocity.y *= -0.6f; // bounce with energy loss
        }
    }
}