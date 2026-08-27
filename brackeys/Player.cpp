#include "Player.hpp"
#include "Vector2Overloads.hpp"
#include "Helper.hpp"
#include <cmath>
#include <iostream>
#include <numbers>



Player::~Player()
{
}

void Player::init() {

	// The line below may pose some trouble
	//m_player = Player{ Entity{Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png"}};
	//m_player = Player{ Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2} };
	getEntity().setPosition(Vector2{ Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2 });
	getEntity().setRadius(8.0f);

	getEntity().setTextures("assets/images/player_horiz.png", "assets/images/player_vert.png");
	getEntity().reloadTextures();
	std::cout << "player birth" << std::endl;
	m_arrow.loadFromFile(s_ArrowTexture);
}

void Player::takeInput(const Camera2D& camera)
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
	else if (IsKeyDown(KEY_ZERO))
		m_entity.setWeapon(Weapon::MaxType);
	
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		m_willAttack = true;

	Vector2 currpos{ getEntity().getPosition() };
	Vector2 centerOffset{ getEntity().getRadius(), getEntity().getRadius() };
	Vector2 mouseWorldPos{ GetScreenToWorld2D(GetMousePosition(), camera) };//unoptimal?
	m_aimVector = Vector2 { Helper::Normalized(mouseWorldPos-(currpos+centerOffset))};

	float theta{ std::acos(Helper::Dot(Vector2{ 0.0f, 1.0f }, m_aimVector)) };
	m_aimDegrees = std::numbers::pi_v<float>;
	//right of player
	if (m_aimVector.x>0) { m_aimDegrees += theta; }
	//left of player
	else { m_aimDegrees = std::numbers::pi_v<float> - theta; }

	m_aimDegrees = m_aimDegrees / std::numbers::pi_v<float> * 180;
	m_aimDegrees *= -1; //ideally remove this if time allows

	getEntity().setAimData(m_aimVector, m_aimDegrees);
}

void Player::think()
{
	m_speed = Helper::getSpeedBasedOnWeaponLevel(m_entity.getWeapon().type());

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
	//draw arrow here
	std::cout << "Aim angle CC: " << m_aimDegrees << "\n";
	m_arrow.render(getEntity().getPosition() + m_aimVector * Constants::g_ScalingSize * 10.0f , Vector2{}, m_aimDegrees, Constants::g_QUARTERALPHA);
	m_entity.Render();
	//DrawRectangleV(getEntity().getPosition() + Vector2 { getEntity().getRadius(), getEntity().getRadius() } + (m_aimVector * Constants::g_ScalingSize*10 ), Vector2{ Constants::g_ScalingSize, Constants::g_ScalingSize }, RED);
	
}