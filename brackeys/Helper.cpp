#include "Helper.hpp"
#include "Constants.hpp"
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

float Helper::Dot(const Vector2& vecA, const Vector2& vecB) {
	return vecA.x * vecB.x + vecA.y * vecB.y;
}

float Helper::getSpeedBasedOnWeaponLevel(Weapon::Type weaponType) {
	float speed{};

	switch (weaponType) {
	case Weapon::Fist_1:
	case Weapon::MaxType:
		speed = Constants::g_SpeedSlow; break;
	case Weapon::Sword_2A:
	case Weapon::Wand_2B:
		speed = Constants::g_SpeedMedium; break;
	case Weapon::Sword_3A:
	case Weapon::Sword_3B:
	case Weapon::Wand_3C:
	case Weapon::Wand_3D:
		speed = Constants::g_SpeedFast; break;
	default: break;
	}

	return speed;
}

int Helper::getMaxHPBasedOnWeaponLevel(Weapon::Type weaponType) {
	int hp{};

	switch (weaponType) {
	case Weapon::Fist_1:
	case Weapon::MaxType:
		hp = Constants::g_HpLow; break;
	case Weapon::Sword_2A:
	case Weapon::Wand_2B:
		hp = Constants::g_HpMedium; break;
	case Weapon::Sword_3A:
	case Weapon::Sword_3B:
	case Weapon::Wand_3C:
	case Weapon::Wand_3D:
		hp = Constants::g_HpHigh; break;
	default: break;
	}

	return hp;
}

int Helper::getMaxXPBasedOnWeaponLevel(Weapon::Type weaponType) {
	int xp{};

	switch (weaponType) {
	case Weapon::Fist_1:
	case Weapon::MaxType:
		xp = Constants::g_XpLow; break;
	case Weapon::Sword_2A:
	case Weapon::Wand_2B:
		xp = Constants::g_XpMedium; break;
	case Weapon::Sword_3A:
	case Weapon::Sword_3B:
	case Weapon::Wand_3C:
	case Weapon::Wand_3D:
		xp = Constants::g_XpHigh; break;
	default: break;
	}

	return xp;
}

Projectile::Data Helper::getProjectileDataBasedOnWeaponType(Weapon::Type weaponType) {
	Projectile::Data data{ -1.f,-1.f, ""};

	switch (weaponType) {
	case Weapon::Sword_3B:
		data = { 10.f * Constants::g_ScalingSize , 40.f, "assets/images/pellet_3b.png", 2.f  }; break;
	case Weapon::Wand_2B:
		data = { 7.5f * Constants::g_ScalingSize, 60.f, "assets/images/pellet_2b.png", 2.f}; break;
	case Weapon::Wand_3C:
		data = { 12.5f * Constants::g_ScalingSize, 120.f, "assets/images/pellet_3c.png", 2.f }; break;
	default:
		break;
	}

	return data;
}