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
	if (IsKeyDown(KEY_W)) {
		m_inputVector += Vector2{ 0.0f,-1.0f };
	}
	if (IsKeyDown(KEY_S)) {
		m_inputVector += { 0.0f,1.0f };
	}
	if (IsKeyDown(KEY_A)) {
		m_inputVector += { -1.0f, 0 };
	}
	if (IsKeyDown(KEY_D)) {
		m_inputVector += { 1.0f, 0.0f };
	}
}

void Player::think()
{
	if (Helper::Length(m_inputVector) > 1) {
		m_inputVector = Helper::Normalized(m_inputVector);
	}
	m_movementVector = Vector2{ 
		m_inputVector.x * GetFrameTime() * 50.0f, 
		m_inputVector.y* GetFrameTime() * 50.0f }; //placholder speed scaling
	m_entity.Move(m_movementVector);
}

void Player::render()
{
	m_entity.Render();
}