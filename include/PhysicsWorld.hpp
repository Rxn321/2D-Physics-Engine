#pragma once

#include <vector>
#include "Body.hpp"


struct PhysicsWorld
{
    Vec2 gravity;
    float G;

    std::vector<Body*> bodies;

    PhysicsWorld();

    void AddBody(Body* body);

    void Update(float dt);

    void ResolveCollisions();

    void MergeBodies(int keep, int remove);

};
