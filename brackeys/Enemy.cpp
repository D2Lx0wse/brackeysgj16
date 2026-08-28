#include "Enemy.hpp"

#include <iostream>

#include "Helper.hpp"
#include "Vector2Overloads.hpp"

#include "Random.h"

Enemy::Enemy()
	: m_mode{ Mode::Roaming }
	, m_clock { -1.0 }
	, m_randomDuration{}
{
}

Enemy::Enemy(const Enemy& enemy) {
	m_mode = enemy.m_mode;
	m_clock = enemy.m_clock;
	m_randomDuration = enemy.m_randomDuration;
}

void Enemy::generateInput(const Vector2& playerPosition) {
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
	m_speed = Helper::getSpeedBasedOnWeaponLevel(m_entity.getWeapon().type());

	if (Helper::Length(m_inputVector) > 1) {
		m_inputVector = Helper::Normalized(m_inputVector);
	}
	m_movementVector = Vector2{
		m_inputVector.x * GetFrameTime() * m_speed,
		m_inputVector.y * GetFrameTime() * m_speed }; //placholder speed scaling
	m_entity.Move(m_movementVector);

	/*
	if (m_willAttack) {
		m_entity.shouldAttack();
		m_willAttack = false;
	}

	m_entity.attack();
	*/
}

void Enemy::render() {
	m_entity.Render();
}

void Enemy::init(Vector2 position) {
	m_mode = Mode::Roaming;

	m_entity.setPosition(position);

	m_entity.setRadius(8.0f);

	m_entity.setTextures(s_HorizontalTexture, s_VerticalTexture);
	m_entity.reloadTextures();

	m_entity.setWeapon(Weapon::Sword_2A);

	if (Random::get(0, 1)) m_entity.setTint(Constants::g_FAKEFRIEND);
	else m_entity.setTint(RED);
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