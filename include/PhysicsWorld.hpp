#pragma once

#include <vector>
#include "Body.hpp"


struct PhysicsWorld
{
    Vec2 gravity;

    std::vector<Body*> bodies;

    PhysicsWorld();

    void AddBody(Body* body);

    void Update(float dt);

    void ResolveCollisions();
};
