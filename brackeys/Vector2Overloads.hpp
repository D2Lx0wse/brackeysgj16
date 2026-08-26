#pragma once

#include <raylib.h>

Vector2 operator+(const Vector2& a, const Vector2& b);

Vector2& operator+=(Vector2& a, const Vector2& b);

Vector2 operator-(const Vector2& a, const Vector2& b);

Vector2& operator-=(Vector2& a, const Vector2& b);

bool operator==(const Vector2& a, const Vector2& b);