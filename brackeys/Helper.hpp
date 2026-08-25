#pragma once

#include "raylib.h"

namespace Helper {
	 bool isColorTheSameBetween(const Color& c1, const Color& c2);
	 float Length(const Vector2& vec);
	 Vector2 Normalized(const Vector2& vec);
	 Vector2 Lerp(const Vector2& vecA, const Vector2& vecB, float lerp);
}