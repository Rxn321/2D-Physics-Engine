#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uPos;
uniform float uScale;
uniform mat4 uProjection;

void main()
{
    vec2 worldPos = aPos * uScale + uPos;
    gl_Position = uProjection * vec4(worldPos, 0.0, 1.0);
}