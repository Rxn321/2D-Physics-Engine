#pragma once

#include "Vector.hpp"

struct Body
{
    Vector position;
    Vector velocity;
    Vector acceleration;

    float mass;
    float radius; // useful for circle collisions later

    Body();
    void Update(float dt);
};