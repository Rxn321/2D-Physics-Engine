cmake_minimum_required(VERSION 3.20)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


add_executable(
    PhysicsEngine

    main.cpp

    src/core/Vec2.cpp
    src/core/Body.cpp
    src/core/PhysicsWorld.cpp
)