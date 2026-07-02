#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uPos;
uniform float uScale;
uniform float uAspect;

void main()
{
    vec2 pos = aPos * uScale;
    pos.x /= uAspect;
    gl_Position = vec4(pos + uPos, 0.0, 1.0);
}