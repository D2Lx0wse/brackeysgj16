#include "Player.hpp"
#include "Vector2Overloads.hpp"
#include "Helper.hpp"


Player::Player(Entity ent)
	:m_entity{ent}
{
}

Player::~Player()
{
}

void Player::takeInput()
{
	m_inputVector = Vector2{};
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
		m_inputVector += Vector2{ 0.0f,-1.0f };
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
		m_inputVector += { 0.0f,1.0f };
	}
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		m_inputVector += { -1.0f, 0 };
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		m_inputVector += { 1.0f, 0.0f };
	}

	if (IsKeyDown(KEY_TWO))
		m_entity.setWeapon(Weapon::Sword_2A);
	else if (IsKeyDown(KEY_THREE))
		m_entity.setWeapon(Weapon::Wand_2B);
}

void Player::think()
{
	if (Helper::Length(m_inputVector) > 1) {
		m_inputVector = Helper::Normalized(m_inputVector);
	}
	m_movementVector = Vector2{ 
		m_inputVector.x * GetFrameTime() * m_speed,
		m_inputVector.y * GetFrameTime() * m_speed }; //placholder speed scaling
	m_entity.Move(m_movementVector);
}

void Player::render()
{
	m_entity.Render();
}