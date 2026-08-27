#include "Enemy.hpp"

#include <iostream>

#include "Helper.hpp"
#include "Vector2Overloads.hpp"

#include "Random.h"

Enemy::Enemy()
	: m_mode{ Mode::Roaming }
	, m_clock { -1.0 }
{
}

Enemy::Enemy(const Enemy& enemy) {
	m_mode = enemy.m_mode;
	m_clock = enemy.m_clock;
}

void Enemy::generateInput() {
	Vector2 randomDirection{};
	static double randomDuration{};

	switch (m_mode) {
	case Mode::Roaming:
		if (m_clock < 0.0) {
			randomDirection = Vector2{ static_cast<float>(Random::get(-1, 1)), static_cast<float>(Random::get(-1, 1)) };
			randomDuration = static_cast<double>(Random::get(1, 3));
			m_clock = GetTime();
			std::cout << m_clock << '\n';
		}
		else if (m_clock >= 0.0 && GetTime() < m_clock + randomDuration) {}
		else
			m_clock = -1.0;

		m_inputVector += randomDirection;
		break;
	case Mode::Attacking:
		
		break;
	default: break;
	}
}

void Enemy::think() {
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
}