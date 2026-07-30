#include "Orbit.hpp"
#include "Body.hpp"
#include <cmath>

namespace Orbit
{
    void CreateUniformThreeBody(
        PhysicsWorld& world,
        float sideLength,
        float mass,
        float radius,
        float G
    )
    {
        // Distance from center to each body
        float R = sideLength / std::sqrt(3.0f);

        // Uniform orbit speed
        float v = std::sqrt(G * mass / sideLength);

        // 120 degree spacing
        const float PI = 3.1415926f;

        float angles[3] =
        {
            0.0f,
            2.0f * PI / 3.0f,
            4.0f * PI / 3.0f
        };

        for(int i = 0; i < 3; i++)
        {
            Body* body = new Body();

            float a = angles[i];

            // Position
            body->position = Vec2(
                R * std::cos(a),
                R * std::sin(a)
            );

            // Tangential velocity
            body->velocity = Vec2(
                -v * std::sin(a),
                 v * std::cos(a)
            );

            body->mass = mass;
            body->radius = radius;

            world.AddBody(body);
        }
    }
}