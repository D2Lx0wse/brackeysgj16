#include "Enemy.hpp"
#include "Helper.hpp"

#include "Vector2Overloads.hpp"

Enemy::Enemy()
	: m_mode{ Mode::Roaming }
{
}

Enemy::Enemy(const Enemy& enemy) {
	m_mode = enemy.m_mode;
}

void Enemy::generateInput() {
	m_inputVector += { 1.0f, 0.0f };
	m_entity.setWeapon(Weapon::Wand_2B);
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
}