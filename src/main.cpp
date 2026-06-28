#include <iostream>
#include "PhysicsWorld.hpp"

int main()
{
    PhysicsWorld world;
    Body ball;
    
    ball.position = Vec2(0, 0);
    
    world.AddBody(&ball);

    for(int i = 0; i < 10; i++)
    {
        world.Update(0.016f);

        std::cout
            << "Pos: " << ball.position.x << ", " << ball.position.y << "\n";
    }
}
