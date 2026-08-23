cmake_minimum_required(VERSION 3.20)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SOURCE FILES
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(PhysicsEngine ${SOURCES} external/glad/src/glad.c)

target_include_directories(PhysicsEngine PRIVATE
    include
    external/glfw/include
    external/glad/include
    external/glm
)


find_package(OpenGL REQUIRED)


add_subdirectory(external/glfw)

target_link_libraries(PhysicsEngine
    OpenGL::GL
    glfw
)

file(COPY ${CMAKE_SOURCE_DIR}/shaders
     DESTINATION ${CMAKE_BINARY_DIR})