#pragma once

#include <cmath>

struct Vec2
{
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(float scalar);
    Vec2& operator/=(float scalar);

    float Magnitude() const;
    float MagnitudeSquared() const;
    Vec2 Normalize() const;
    float Dot(const Vec2& other) const;
    float Distance(const Vec2& other) const;

    float Length() const;
};