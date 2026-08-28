#pragma once
#include "raylib.h"
#include "Brackeys2DTexture.hpp"
#include "Circle.hpp"
#include <string_view>
#include <string>

#include "Weapon.hpp"

class Entity
{
private:
	enum Direction {
		up,
		right,
		down,
		left,
	};

public:
	Entity(Vector2 position, std::string_view path_horiz, std::string_view path_vert, Direction dir = up, float radius = 5.0f);
	Entity(const Entity& entity) = delete; // Currently, copy ctor/assignment does a shallow copy, which leads to corrupted/duplicated textures
	Entity(Entity& entity) = default;

	Entity() = default;
	//~Entity();
	void Render();
	void Move(Vector2 vector);
	void Move(float vectorX, float vectorY);
	void reloadTextures();

	Circle getCircle();

	//getters and setters
	float getRadius() const { return m_radius; }
	void setRadius( float radius);
	Vector2 getPosition() const { return m_position; }
	void setPosition(const Vector2& position) { m_position = position; }
	Weapon& getWeapon() { return m_weapon; }
	void setWeapon(Weapon::Type weaponType, bool isEnemy = false) { m_weapon.setWeapon(weaponType, isEnemy); }
	void setTextures(std::string_view path_horizontal, std::string_view path_vertical);
	void setTint(Color tint) { m_tint = tint; }
	void setAimData(Vector2 vector, float degrees) { m_aimingVector = vector; m_aimingDegrees = degrees; }

	void setAttackingTrue() { if (m_weapon.type() != Weapon::Wand_2B && m_weapon.type() != Weapon::Wand_3C) m_isAttacking = true; }

	bool getShouldShoot() const { return m_shouldShoot; }
	void setShouldShootFalse() { m_shouldShoot = false; }

	bool isWeaponAtMaxLevel() const;

	void attack();
	void shoot();

private:
	Vector2 m_position{};
	Vector2 m_aimingVector{};
	float m_aimingDegrees{};
	Brackeys2DTexture m_textureHoriz{};
	Brackeys2DTexture m_textureVert{};
	Direction m_direction{};
	std::string m_textureHorizPath{};
	std::string m_textureVertPath{};
	float m_radius{};
	Color m_tint;
	Weapon m_weapon{};
	bool m_isAttacking{ false };
	bool m_shouldShoot{ false };

	bool m_shouldGetTime{ true };
	double m_attackStartTime{};
};

