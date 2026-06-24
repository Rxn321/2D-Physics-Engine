cmake_minimum_required(VERSION 3.20)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


add_executable(
    PhysicsEngine

    main.cpp

    src/Vec2.cpp
    src/Body.cpp
    src/PhysicsWorld.cppc
)