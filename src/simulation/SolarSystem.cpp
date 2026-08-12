#include "SolarSystem.hpp"
#include "Body.hpp"
#include "Orbit.hpp"
#include <cmath>

namespace SolarSystem
{
    void Create(PhysicsWorld& world)
    {
        Body* sun = new Body();

        sun->position = Vec2(0, 0);
        sun->mass = 1000.0f;
        sun->radius = 5.0f;

        Body* planet1 = new Body();

        planet1->position = Vec2(30, 0);
        planet1->mass = 10.0f;
        planet1->radius = 1.0f;
        planet1->velocity = Vec2(0, 15);

        //world.AddBody(sun);
        //world.AddBody(planet1);

        Orbit::CreateUniformThreeBody(world, 50, 200, 2.0f, 10.0f);
    }
}