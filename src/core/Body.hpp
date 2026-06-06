#pragma once

#include "Vector.hpp"

struct Body
{
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    float mass;
    float radius; // useful for circle collisions later

    Body();
    void Update(float dt);
};