#include "Player.hpp"
#include "Vector2Overloads.hpp"
#include "Helper.hpp"


Player::Player(Entity ent)
{
	Player(ent.getPosition());
}

Player::Player(Vector2 position)
	:m_entity{}
{
	m_entity.setPosition(position);

	m_entity.setTextures(s_HorizontalTexture, s_VerticalTexture);
	m_entity.reloadTextures();
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

	if (IsKeyDown(KEY_ONE))
		m_entity.setWeapon(Weapon::Fist_1);
	else if (IsKeyDown(KEY_TWO))
		m_entity.setWeapon(Weapon::Sword_2A);
	else if (IsKeyDown(KEY_THREE))
		m_entity.setWeapon(Weapon::Wand_2B);
	else if (IsKeyDown(KEY_FOUR))
		m_entity.setWeapon(Weapon::Sword_3A);
	else if (IsKeyDown(KEY_FIVE))
		m_entity.setWeapon(Weapon::Sword_3B);
	else if (IsKeyDown(KEY_SIX))
		m_entity.setWeapon(Weapon::Wand_3C);
	else if (IsKeyDown(KEY_SEVEN))
		m_entity.setWeapon(Weapon::Wand_3D);
	
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		m_willAttack = true;
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

	if (m_willAttack) {
		m_entity.shouldAttack();
		m_willAttack = false;
	}

	m_entity.attack();
}

void Player::render()
{
	m_entity.Render();
}