cmake_minimum_required(VERSION 3.20)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SOURCE FILES
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/core/*.cpp
    src/renderer/*.cpp
)

add_executable(PhysicsEngine ${SOURCES} external/glad/glad.c)

target_include_directories(PhysicsEngine PRIVATE
    include
    external/glad
    external/glfw/include
)


find_package(OpenGL REQUIRED)


add_subdirectory(external/glfw)

target_link_libraries(PhysicsEngine
    glfw
    OpenGL::GL
)