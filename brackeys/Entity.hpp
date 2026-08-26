#pragma once
#include "raylib.h"
#include "Brackeys2DTexture.hpp"
#include "Circle.hpp"
#include <string_view>

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
	Entity() = default;
	~Entity();
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
	void setWeapon(Weapon::Type weaponType) { m_weapon.setWeapon(weaponType); }
	void setTextures(std::string_view path_horizontal, std::string_view path_vertical);

	void shouldAttack() { m_isAttacking = true; }

	void attack();

private:
	Vector2 m_position{};
	Brackeys2DTexture m_textureHoriz{};
	Brackeys2DTexture m_textureVert{};
	Direction m_direction{};
	std::string_view m_textureHorizPath{};
	std::string_view m_textureVertPath{};
	float m_radius{};
	
	Weapon m_weapon{};
	bool m_isAttacking{ false };

	bool m_renderAttack{ false };
};

