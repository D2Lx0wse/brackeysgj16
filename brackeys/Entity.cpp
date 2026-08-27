#include "Entity.hpp"
#include <string_view>
#include <iostream>
#include <cmath>

#include "Vector2Overloads.hpp"

void Entity::Render() {
	float weaponRotation{};
	// Starts off from player position, is moved based on where the player is facing
	Vector2 weaponPosition{ m_position };
	Vector2 weaponSize{ m_weapon.texture().width(), m_weapon.texture().height() }; // Used to mirror the texture

	switch (m_direction) {
	case up:
		m_textureVert.render(m_position, Vector2{}, 180.f);

		weaponRotation = 0.0f;
		weaponPosition += Vector2{ getRadius() * -1.0f, getRadius() * -1.0f };
		weaponSize.x *= -1.0f;
		break;
	case right:
		m_textureHoriz.render(m_position, Vector2{ -m_textureHoriz.width(), 0.0f });

		weaponRotation = 90.0f;
		weaponPosition += Vector2{ getRadius(), getRadius() };
		break;
	case down:
		m_textureVert.render(m_position);
		
		weaponRotation = 180.0f;
		weaponPosition += Vector2{ getRadius(), getRadius() };
		break;
	case left:
		m_textureHoriz.render(m_position);

		weaponRotation = -90.0f;
		weaponPosition += Vector2{ getRadius() * -1.0f, getRadius() };
		weaponSize.x *= -1.0f;
		break;
	default:
		std::cerr << "impossible direction!!!";
		break;
	}

	m_weapon.texture().render(weaponPosition, weaponSize, weaponRotation);

	if (m_isAttacking)
		m_weapon.attackTexture().render(
			getPosition()  +
			(m_aimingVector *getRadius() * 3.0f) - //aiming vector first thing here
			Vector2{ (
				m_weapon.attackTexture().width() 
				- (getRadius() * 2.0f)
				)/ 2.0f
			,	(m_weapon.attackTexture().height()
				- (getRadius() * 2.0f)
				) / 2.0f
			}
		, Vector2{}, m_aimingDegrees);//aiming degrees here last thing
}

void Entity::Move(float vectorX, float vectorY) {
	Move(Vector2{ vectorX, vectorY });
}

void Entity::Move(Vector2 vector) {
	if (vector == Vector2{ 0.0f, 0.0f })
		return;

	m_position.x += vector.x;
	m_position.y += vector.y;
	if (std::abs(vector.x) > std::abs(vector.y)) {
		if (vector.x > 0) {
			m_direction = right;
		}
		else {
			m_direction = left;
		}
	}
	else {
		if (vector.y < 0) {
			m_direction = up;
		}
		else {
			m_direction = down;
		}
	}
}

void Entity::attack() {
	if (!m_isAttacking)
		return;

	static bool shouldGetTime{ true };
	static double currentTime{};

	if (shouldGetTime)
	currentTime = GetTime();

	if (GetTime() < currentTime + 0.5) {
		shouldGetTime = false;

	}
	else {
		m_isAttacking = false;
		shouldGetTime = true;
	}
}

void Entity::reloadTextures() {
	m_textureHoriz.loadFromFile(m_textureHorizPath);
	m_textureVert.loadFromFile(m_textureVertPath);

	m_weapon.setWeapon(Weapon::Sword_2A);
	//m_weapon.texture().loadFromFile(Weapon::s_TextureFilepaths[m_weapon.type()]);
}

void Entity::setRadius(float radius) {
	m_radius = std::abs(radius) * Constants::g_ScalingSize;
}

Circle Entity::getCircle() {
	return Circle(getPosition(), getRadius());
}

void Entity::setTextures(std::string_view path_horizontal, std::string_view path_vertical) {
	m_textureHorizPath = path_horizontal;
	m_textureHoriz.loadFromFile(m_textureHorizPath);
	
	m_textureVertPath = path_vertical;
	m_textureVert.loadFromFile(m_textureVertPath);
}

Entity::Entity(Vector2 position, std::string_view path_horiz, std::string_view path_vert, Direction dir, float radius)
	:m_position{ position }, m_direction{ dir }, m_textureHorizPath{ path_horiz }, m_textureVertPath{ path_vert }
	, m_weapon{}
{
	m_textureHoriz.loadFromFile(m_textureHorizPath);
	m_textureVert.loadFromFile(m_textureVertPath);
	setRadius(radius);
}