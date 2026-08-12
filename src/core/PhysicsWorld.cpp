#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld()
{
    gravity = Vec2(0.0f, 0.0f);
    G = 10.0f; // gravitational constant
}

void PhysicsWorld::AddBody(Body* body)
{
    bodies.push_back(body);
}

void PhysicsWorld::Update(float dt)
{
    // Apply gravity between all bodies
    for (size_t i = 0; i < bodies.size(); i++)
    {
        for (size_t j = i + 1; j < bodies.size(); j++)
        {
            Body* a = bodies[i];
            Body* b = bodies[j];


            Vec2 direction = b->position - a->position;

            float distance = direction.Length();


            if (distance > 0.01f)
            {
                Vec2 normal = direction * (1.0f / distance);


                float forceMagnitude =
                    G * a->mass * b->mass /
                    (distance * distance);


                Vec2 force = normal * forceMagnitude;


                a->ApplyForce(force);
                b->ApplyForce(force * -1.0f);
            }
        }
    }
    for (Body* body : bodies)
    {
        body->Update(dt);
        body->trail.push_back(body->position);

        if (body->trail.size() > 2000)
        {
            body->trail.erase(body->trail.begin());
        }
    }
    ResolveCollisions();

}

void PhysicsWorld::ResolveCollisions()
{
    for (size_t i = 0; i < bodies.size(); i++)
    {
        for (size_t j = i + 1; j < bodies.size(); j++)
        {
            Body* a = bodies[i];
            Body* b = bodies[j];

            if (!a->alive || !b->alive)
                continue;

            Vec2 delta = a->position - b->position;
            float distSquared = delta.x * delta.x + delta.y * delta.y;
            float minDist = a->radius + b->radius;

            if (distSquared <= minDist * minDist)
            {
                if (a->mass >= b->mass)
                    MergeBodies(i, j);
                else
                    MergeBodies(j, i);
            }
        }
    }

bodies.erase(
    std::remove_if(bodies.begin(), bodies.end(),
        [](Body* b)
        {
            if (!b->alive)
            {
                delete b;
                return true;
            }
            return false;
        }),
    bodies.end());
}
    

void PhysicsWorld::MergeBodies(int mainIndex, int absorbedIndex)
{
    Body* main = bodies[mainIndex];
    Body* absorbed = bodies[absorbedIndex];

    float totalMass = main->mass + absorbed->mass;

    main->velocity =
        (main->velocity * main->mass +
         absorbed->velocity * absorbed->mass) / totalMass;

    main->position =
        (main->position * main->mass +
         absorbed->position * absorbed->mass) / totalMass;

    main->mass = totalMass;

    main->radius = std::sqrt(
        main->radius * main->radius +
        absorbed->radius * absorbed->radius
    );

    absorbed->alive = false;
}