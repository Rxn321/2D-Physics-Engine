#pragma once

#include <vector>
#include "Body.hpp"

constexpr float WORLD_WIDTH = 200.0f;
constexpr float WORLD_HEIGHT = 200.0f;

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
