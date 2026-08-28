#pragma once

#include "raylib.h"
#include "Weapon.hpp"

namespace Helper {
	 bool isColorTheSameBetween(const Color& c1, const Color& c2);
	 float Length(const Vector2& vec);
	 Vector2 Normalized(const Vector2& vec);
	 Vector2 Lerp(const Vector2& vecA, const Vector2& vecB, float lerp);
	 float Dot(const Vector2& vecA, const Vector2& vecB);
	 float getSpeedBasedOnWeaponLevel(Weapon::Type weaponType);
	 int getMaxHPBasedOnWeaponLevel(Weapon::Type weaponType);
	 int getMaxXPBasedOnWeaponLevel(Weapon::Type weaponType);
}