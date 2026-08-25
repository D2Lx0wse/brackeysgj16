#include "Helper.hpp"
#include <cmath>

bool Helper::isColorTheSameBetween(const Color& c1, const Color& c2) {
	return	c1.r == c2.r &&
			c1.g == c2.g &&
			c1.b == c2.b &&
			c1.a == c2.a;
}

float Helper::Length(const Vector2& vec) {
	return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 Helper::Normalized(const Vector2& vec) {
	float length = Length(vec);
	if ( length > 0) {
		return Vector2{ vec.x / length,vec.y / length };
	}
	else{ return vec; }
}

Vector2 Helper::Lerp(const Vector2& vecA, const Vector2& vecB, float lerp) {
	Vector2 diff{ vecA.x - vecB.x, vecA.y - vecA.y };
	Vector2 scaledDiff{ diff.x * lerp, diff.y * lerp };
	return Vector2{ vecB.x + scaledDiff.x, vecB.y + scaledDiff.y };
}