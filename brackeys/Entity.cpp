#include "Entity.hpp"
#include <string_view>
#include <iostream>
#include <cmath>

#include "Vector2Overloads.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

void Entity::Render() {
	float weaponRotation{};
	// Starts off from player position, is moved based on where the player is facing
	Vector2 weaponPosition{ m_position };
	Vector2 weaponSize{ m_weapon.texture().width(), m_weapon.texture().height() }; // Used to mirror the texture

	switch (m_direction) {
	case up:
		m_textureVert.render(m_position, Vector2{}, 180.f, m_tint);

		weaponRotation = 0.0f;
		weaponPosition += Vector2{ getRadius() * -1.0f, getRadius() * -1.0f };
		weaponSize.x *= -1.0f;
		break;
	case right:
		m_textureHoriz.render(m_position, Vector2{ -m_textureHoriz.width(), 0.0f }, 0.0f, m_tint);

		weaponRotation = 90.0f;
		weaponPosition += Vector2{ getRadius(), getRadius() };
		break;
	case down:
		m_textureVert.render(m_position, Vector2{}, 0.0f, m_tint);
		
		weaponRotation = 180.0f;
		weaponPosition += Vector2{ getRadius(), getRadius() };
		break;
	case left:
		m_textureHoriz.render(m_position, Vector2{}, 0.0f, m_tint);

		weaponRotation = -90.0f;
		weaponPosition += Vector2{ getRadius() * -1.0f, getRadius() };
		weaponSize.x *= -1.0f;
		break;
	default:
		std::cerr << "impossible direction!!!";
		break;
	}

	m_weapon.texture().render(weaponPosition, weaponSize, weaponRotation);

	//good graphics
	if (m_isAttacking)
		m_weapon.attackTexture().render(
			getPosition()  +
			(m_aimingVector *getRadius() * 3.0f * ((m_weapon.type()==Weapon::Wand_3D)?2.f:1.f)) - //aiming vector first thing here
			Vector2{ (
				m_weapon.attackTexture().width() 
				- (getRadius() * 2.0f)
				)/ 2.0f
			,	(m_weapon.attackTexture().height()
				- (getRadius() * 2.0f)
				) / 2.0f
			}
		, Vector2{}, m_aimingDegrees,//aiming degrees here last thing
			Color{ 255,255,255, static_cast<unsigned char>(((std::pow(((m_attackStartTime - GetTime() + m_weapon.attackDuration() ) / m_weapon.attackDuration() ), 10.0f)*200.f)+
														((m_attackStartTime - GetTime() + m_weapon.attackDuration()) / m_weapon.attackDuration())*55.f) )}
			);
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
	if (not m_isAttacking) { return; }
	//from here on out WE ARE ATTACKING
	 
	//here lie two static local variables that were being used by multiple entities at the same time

	if (m_shouldGetTime)
		m_attackStartTime = GetTime();

	if (GetTime() < m_attackStartTime + m_weapon.attackDuration()) {

		//std::cout << "Curr time is " << GetTime() << " and we started attacking at " << m_attackStartTime << " and we will attack again at " << m_attackStartTime + m_weapon.attackDuration() << "\n";
		m_shouldGetTime = false;

	}
	else {//finish attack
		m_isAttacking = false;
		m_shouldGetTime = true;
	}
}

void Entity::slash(std::vector<Enemy>& enemies) {//it may look weird... but it works
	if (!m_isAttacking) {
#ifdef _DEBUG
		std::cout << "slash sound effect\n";
#endif

		Vector2 slashposition{
			getPosition() +
			(m_aimingVector * getRadius() * 3.0f * ((m_weapon.type() == Weapon::Wand_3D) ? 2.f : 1.f)) - //aiming vector first thing here
			Vector2{ (
				m_weapon.attackTexture().width()
				- (getRadius() * 2.0f)
				) / 2.0f
			,	(m_weapon.attackTexture().height()
				- (getRadius() * 2.0f)
				) / 2.0f
			}
		};

		for (auto& enemy : enemies) {
			if (CheckCollisionCircles(slashposition, m_weapon.attackTexture().width() / 2.f, enemy.entity().getPosition(), enemy.entity().getCircle().radius)) {
#ifdef _DEBUG
					std::cout << "Enemy hit!\n ";
#endif
					enemy.decreaseHP(static_cast<int>(m_weapon.weaponDamage()));
			}
		}
	}
}


void Entity::slash(Player& player) {
	if (!m_isAttacking) {
#ifdef _DEBUG
		std::cout << "slash sound effect\n";
#endif

		Vector2 slashposition{
			getPosition() +
			(m_aimingVector * getRadius() * 3.0f * ((m_weapon.type() == Weapon::Wand_3D) ? 2.f : 1.f)) - //aiming vector first thing here
			Vector2{ (
				m_weapon.attackTexture().width()
				- (getRadius() * 2.0f)
				) / 2.0f
			,	(m_weapon.attackTexture().height()
				- (getRadius() * 2.0f)
				) / 2.0f
			}
		};

		if (CheckCollisionCircles(slashposition, m_weapon.attackTexture().width() / 2.f, player.getEntity().getPosition(), player.getEntity().getCircle().radius)) {
#ifdef _DEBUG
			std::cout << "Player hit!\n ";
#endif
			player.decreaseHP(static_cast<int>(m_weapon.weaponDamage()));
		}
	}
}

void Entity::shoot() {
	m_shouldShoot = true;
}

void Entity::reloadTextures() {
	m_textureHoriz.loadFromFile(m_textureHorizPath);
	m_textureVert.loadFromFile(m_textureVertPath);
	
	// Decomment if weapons do not work
	// m_weapon.setWeapon(Weapon::Fist_1);
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

bool Entity::isWeaponAtMaxLevel() const {
	return (m_weapon.type() == Weapon::Sword_3A ||
			m_weapon.type() == Weapon::Sword_3B ||
			m_weapon.type() == Weapon::Wand_3C ||
			m_weapon.type() == Weapon::Wand_3D);
}
