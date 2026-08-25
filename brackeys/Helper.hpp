#pragma once

#include "raylib.h"

namespace Helper {
	 bool isColorTheSameBetween(const Color& c1, const Color& c2);
	 float vec2Length(const Vector2& vec);
	 Vector2 vec2Normalized(const Vector2& vec);
}