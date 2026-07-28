#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld()
{
    gravity = Vec2(0.0f, 0.0f);
    G = 50.0f; // gravitational constant
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


        //trail position
        body->trail.push_back(body->position);

        //trail length
        if (body->trail.size() > 200)
        {
            body->trail.erase(body->trail.begin());
        }
    }
        ResolveCollisions();
}

/*        
        body->ApplyForce(gravity * body->mass);
        // floor collision
        float floorY = -7.5f + body->radius;
        float leftX = -10.0f + body->radius;
        float rightX = 10.0f - body->radius;

        if (body->position.y < floorY)
        {
            body->position.y = floorY;
            body->velocity.y *= -0.6f; //loss
        }
        //left
        if (body->position.x < leftX)
        {
            body->position.x = leftX;
            body->velocity.x *= -0.6f;
        }

        // right
        if (body->position.x > rightX)
        {
            body->position.x = rightX;
            body->velocity.x *= -0.6f;
        }
    }
*/


void PhysicsWorld::ResolveCollisions()
{
    for (size_t i = 0; i < bodies.size(); i++)
    {
        for (size_t j = i + 1; j < bodies.size(); j++)
        {
            Body* a = bodies[i];
            Body* b = bodies[j];

            Vec2 delta = a->position - b->position;
            float dist = delta.Length();
            float minDist = a->radius + b->radius;

            if (dist < minDist && dist > 0.0f)
            {
                Vec2 normal = delta * (1.0f / dist);

                float overlap = minDist - dist;
                a->position += normal * (overlap * 0.5f);
                b->position -= normal * (overlap * 0.5f);

                Vec2 relativeVel = a->velocity - b->velocity;
                float velAlongNormal = relativeVel.x * normal.x + relativeVel.y * normal.y;

                if (velAlongNormal < 0)
                {
                    float restitution = 1.0f; // bounce
                    float impulse = -(1 + restitution) * velAlongNormal / (1/a->mass + 1/b->mass);

                    Vec2 impulseVec = normal * impulse;
                    a->velocity += impulseVec * (1.0f / a->mass);
                    b->velocity -= impulseVec * (1.0f / b->mass);
                }
            }
        }
    }
}