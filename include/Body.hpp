#pragma once

#include "Vec2.hpp"
#include <vector>

struct Body
{
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    float mass;
    float radius;

    bool alive = true;

    std::vector<Vec2> trail; 

    Body();
    void Update(float dt);
    void ApplyForce(Vec2 force);
};