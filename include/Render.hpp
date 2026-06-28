#pragma once

#include "Body.hpp"

class Render
{
public:
    void Init();
    void DrawBody(const Body& body);

private:
    unsigned int VAO, VBO, EBO;
};