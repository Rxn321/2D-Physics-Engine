#include "Body.hpp"

Body::Body()
{
    position = Vec2(0.0f, 0.0f);
    velocity = Vec2(0.0f, 0.0f);
    acceleration = Vec2(0.0f, 0.0f);

    mass = 1.0f;
    radius = 10.0f;
    
    Body* sun = new Body();

    sun->position = Vec2(0,0);
    sun->mass = 1000;
    sun->radius = 40;

    Body* planet = new Body();

    planet->position = Vec2(300,0);
    planet->mass = 10;

    planet->velocity = Vec2(0,13);

}

void Body::Update(float dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = Vec2(0,0);
}

void Body::ApplyForce(Vec2 force)
{
    acceleration += force / mass;
}