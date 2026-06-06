#include "Body.hpp"

Body::Body()
{
    position = Vec2(0.0f, 0.0f);
    velocity = Vec2(0.0f, 0.0f);
    acceleration = Vec2(0.0f, 0.0f);

    mass = 1.0f;
    radius = 10.0f;
}

void Body::Update(float dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
}