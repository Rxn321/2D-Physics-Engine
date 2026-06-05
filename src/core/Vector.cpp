#include "Vector.hpp"

// Constructors
Vec2::Vec2() : x(0.0f), y(0.0f) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

// Operators
Vec2 Vec2::operator+(const Vec2& other) const
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(float scalar) const
{
    return Vec2(x / scalar, y / scalar);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

// Math
float Vec2::Magnitude() const
{
    return std::sqrt(x * x + y * y);
}

float Vec2::MagnitudeSquared() const
{
    return x * x + y * y;
}

Vec2 Vec2::Normalize() const
{
    float mag = Magnitude();
    if (mag == 0.0f) return Vec2(0.0f, 0.0f);
    return Vec2(x / mag, y / mag);
}

float Vec2::Dot(const Vec2& other) const
{
    return x * other.x + y * other.y;
}

float Vec2::Distance(const Vec2& other) const
{
    return (*this - other).Magnitude();
}