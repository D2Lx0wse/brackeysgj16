#include "Helper.hpp"
#include <cmath>

bool Helper::isColorTheSameBetween(const Color& c1, const Color& c2) {
	return	c1.r == c2.r &&
			c1.g == c2.g &&
			c1.b == c2.b &&
			c1.a == c2.a;
}

float Helper::vec2Length(const Vector2& vec) {
	return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 Helper::vec2Normalized(const Vector2& vec) {
	float length = vec2Length(vec);
	if ( length > 0) {
		return Vector2{ vec.x / length,vec.y / length };
	}
	else{ return vec; }
}