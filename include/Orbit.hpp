#pragma once

#include "PhysicsWorld.hpp"

namespace Orbit
{
    void CreateUniformThreeBody(
        PhysicsWorld& world,
        float sideLength,
        float mass,
        float radius,
        float G
    );
}