#include "Body.hpp"

Body::Body()
{
    position = Vec2(0, 0);
    velocity = Vec2(0, 0);
    acceleration = Vec2(0, 0);

    mass = 1.0f;
    radius = 10.0f;
}

void Body::Update(float dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
}