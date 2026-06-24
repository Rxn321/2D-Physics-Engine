#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld()
{
    gravity = Vec2(0.0f, 9.8f);
}

void PhysicsWorld::AddBody(Body* body)
{
    bodies.push_back(body);
}

void PhysicsWorld::Update(float dt)
{
    for (Body* body : bodies)
    {

        body->ApplyForce(
            gravity * body->mass
        );

        body->Update(dt);

    }

}