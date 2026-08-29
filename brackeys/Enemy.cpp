#include "Enemy.hpp"

#include <iostream>
#include <numbers>

#include "Helper.hpp"
#include "Vector2Overloads.hpp"

#include "Random.h"

Enemy::Enemy()
	: m_mode{ Mode::Roaming }
	, m_isDead { false }
	, m_clock { -1.0 }
	, m_randomDuration{}
	, m_willAttack{ false }
{
}

Enemy::Enemy(const Enemy& enemy) {
	m_mode = enemy.m_mode;
	m_isDead = enemy.m_isDead;
	m_clock = enemy.m_clock;
	m_randomDuration = enemy.m_randomDuration;
	m_willAttack = enemy.m_willAttack;
}

void Enemy::generateInput(const Vector2& playerPosition) {
	if (isDead())
		return;

	Vector2 randomDirection{};
	
	switch (m_mode) {
	case Mode::Roaming:
		if (m_clock < 0.0) {
			m_inputVector = Vector2{};
			randomDirection = Vector2{ static_cast<float>(Random::get(-1, 1)), static_cast<float>(Random::get(-1, 1)) };
			m_randomDuration = static_cast<double>(Random::get(1, 3));
			m_inputVector += randomDirection;
			m_clock = GetTime();
		}
		else if (m_clock >= 0.0 && GetTime() < m_clock + m_randomDuration) {}
		else {
			m_clock = -1.0;
			randomDirection = Vector2{};
			m_randomDuration = 0.0;
		}
		
		break;
	case Mode::Attacking:
		// The enemy follows the player
		if (m_entity.getPosition().x - playerPosition.x < 0.0f + m_entity.getRadius())
			m_inputVector.x = 1.0f;
		else if (m_entity.getPosition().x - playerPosition.x >= 0.0f - m_entity.getRadius())
			m_inputVector.x = -1.0f;

		if (m_entity.getPosition().y - playerPosition.y < 0.0f + m_entity.getRadius())
			m_inputVector.y = 1.0f;
		else if (m_entity.getPosition().y - playerPosition.y >= 0.0f - m_entity.getRadius())
			m_inputVector.y = -1.0f;

		// If the enemy and the player touch, the enemy stops moving
		if (CheckCollisionRecs(Rectangle{ m_entity.getPosition().x, m_entity.getPosition().y, m_entity.getRadius() * 2.0f, m_entity.getRadius() * 2.0f },
			Rectangle{ playerPosition.x, playerPosition.y, m_entity.getRadius() * 2.0f, m_entity.getRadius() * 2.0f }))
			m_inputVector = Vector2{ 0.0f, 0.0f };

		m_willAttack = Random::get(0, 1);
		if (m_willAttack) {
			Vector2 currpos{ entity().getPosition() };
			Vector2 centerOffset{ entity().getRadius(), entity().getRadius() };
			m_aimVector = Vector2{ Helper::Normalized(playerPosition - (currpos + centerOffset)) };

			float theta{ std::acos(Helper::Dot(Vector2{ 0.0f, 1.0f }, m_aimVector)) };
			m_aimDegrees = std::numbers::pi_v<float>;
			//right of player
			if (m_aimVector.x > 0) { m_aimDegrees += theta; }
			//left of player
			else { m_aimDegrees = std::numbers::pi_v<float> -theta; }

			m_aimDegrees = m_aimDegrees / std::numbers::pi_v<float> *180;
			m_aimDegrees *= -1; //ideally remove this if time allows

			entity().setAimData(m_aimVector, m_aimDegrees);
		}

		break;
	default: break;
	}
	/*
	switch(rand 1-4){
	1
	vector{0 1}
	degrees = 0
	2...

	}

	*/
}

void Enemy::think() {
	if (isDead())
		return;

	changeWeaponAndStatistics();

	if (Helper::Length(m_inputVector) > 1) {
		m_inputVector = Helper::Normalized(m_inputVector);
	}
	m_movementVector = Vector2{
		m_inputVector.x * GetFrameTime() * m_speed,
		m_inputVector.y * GetFrameTime() * m_speed }; //placholder speed scaling
	m_entity.Move(m_movementVector);

	
	if (m_willAttack) {
		m_entity.setAttackingTrue();
		m_willAttack = false;
	}

	m_entity.attack();
}

void Enemy::render() {
	if (isDead())
		return;

	m_entity.Render();
}

void Enemy::init(Vector2 position) {
	m_mode = Mode::Roaming;

	m_isDead = false;

	m_entity.setPosition(position);

	m_entity.setRadius(8.0f);

	m_entity.setTextures(s_HorizontalTexture, s_VerticalTexture);
	m_entity.reloadTextures();

	m_entity.setWeapon(static_cast<Weapon::Type>(Random::get(0, Weapon::MaxType-1)), true);
	changeWeaponAndStatistics();

	if (Random::get(0, 1)) m_entity.setTint(Constants::g_FAKEFRIEND);
	else m_entity.setTint(RED);
}

void Enemy::death() {
	m_isDead = true;

	// Outside the scene so that it is not visible/interactable
	m_entity.setPosition(Vector2{ -1000.0f, -1000.0f });
}

void Enemy::setMode(Mode mode) {
	if (m_mode != mode) {
		m_mode = mode;

		// Reset the movement
		m_clock = -1.0f;
		m_inputVector = Vector2{ 0.0f, 0.0f };
		m_randomDuration = double{};
	}
}

int Enemy::dropXP() {
	int xpAmount{};

	switch (m_entity.getWeapon().type()) {
	case Weapon::Fist_1:
	case Weapon::MaxType:
		xpAmount = Constants::g_XpLow / 4; break;
	case Weapon::Sword_2A:
	case Weapon::Wand_2B:
		xpAmount = Constants::g_XpMedium / 4; break;
	case Weapon::Sword_3A:
	case Weapon::Sword_3B:
	case Weapon::Wand_3C:
	case Weapon::Wand_3D:
		xpAmount = Constants::g_XpHigh / 5; break;
	default: break;
	}

	return xpAmount;
}

// If weapon type changed, set m_currentWeaponType and statistics accordingly
void Enemy::changeWeaponAndStatistics() {
	if (m_currentWeaponType != entity().getWeapon().type()) {
		m_currentWeaponType = entity().getWeapon().type();

		m_maxHp = Helper::getMaxHPBasedOnWeaponLevel(m_currentWeaponType);
		heal();

		m_speed = Helper::getSpeedBasedOnWeaponLevel(m_currentWeaponType);
	}
}