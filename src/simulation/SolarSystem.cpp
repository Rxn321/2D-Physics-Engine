#include "SolarSystem.hpp"
#include "Body.hpp"

namespace SolarSystem
{
    void Create(PhysicsWorld& world)
    {
        // Sun
        Body* sun = new Body();
        sun->position = Vec2(0, 0);
        sun->mass = 1000.0f;
        sun->radius = 5.0f;

        // Planet
        Body* planet = new Body();
        planet->position = Vec2(30, 0);
        planet->mass = 10.0f;
        planet->radius = 1.0f;

        // Initial sideways velocity
        planet->velocity = Vec2(0, 40);

        world.AddBody(sun);
        world.AddBody(planet);
    }
}