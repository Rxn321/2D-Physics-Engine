#include "Body.hpp"

Body::Body()
{
    position = Vector(0, 0);
    velocity = Vector(0, 0);
    acceleration = Vector(0, 0);

    mass = 1.0f;
    radius = 10.0f;
}

void Body::Update(float dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
}