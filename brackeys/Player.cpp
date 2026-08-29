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
	getEntity().setTint(WHITE);
	std::cout << "player birth" << std::endl;

	m_isDead = false;

	m_xp = 0;
	m_entity.setWeapon(Weapon::Fist_1);
	changeWeaponAndStatistics();

	m_currProjectile = Projectile{};

	m_arrow.loadFromFile(s_ArrowTexture);
}

void Player::takeInput(const Camera2D& camera)
{
	if (isDead())
		return;

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

#if _DEBUG
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
#endif

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

void Player::think(std::vector<Enemy>& enemies)
{
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
		m_entity.slash(enemies);
		m_entity.setAttackingTrue();
		m_entity.shoot();
		m_willAttack = false;
	}
	
	m_entity.attack();

	if (m_entity.getShouldShoot())
	{	
		Projectile::Data projDate{ Helper::getProjectileDataBasedOnWeaponType(m_currentWeaponType) };
		if (projDate.speed == -1.f){}
		else if (!m_currProjectile.isAlive()){
			m_currProjectile.init(m_aimVector, m_aimDegrees, &m_entity, projDate, m_entity.getPosition());
		}

		m_entity.setShouldShootFalse();
	}

	if (m_currProjectile.isAlive())
	{
		m_currProjectile.calc(enemies);
	}
}

void Player::render()
{
	if (isDead())
		return;

	//draw arrow here
	//std::cout << "Aim angle CC: " << m_aimDegrees << "\n";
	m_arrow.render(getEntity().getPosition() + m_aimVector * Constants::g_ScalingSize * 10.0f , Vector2{}, m_aimDegrees, Constants::g_QUARTERALPHA);
	m_entity.Render();
	if (m_currProjectile.isAlive())
	{
		m_currProjectile.render();
	}
	//DrawRectangleV(getEntity().getPosition() + Vector2 { getEntity().getRadius(), getEntity().getRadius() } + (m_aimVector * Constants::g_ScalingSize*10 ), Vector2{ Constants::g_ScalingSize, Constants::g_ScalingSize }, RED);
	
}

void Player::increaseXP(int xp) {
	m_xp += xp;

	if (m_xp > m_maxXp)
		m_xp = m_maxXp;
}

void Player::decreaseHP(int hp) {
	m_hp -= hp;

	if (m_hp < 0)
		m_hp = 0;
}

void Player::death() {
	m_isDead = true;
}

// If weapon type changed, set m_currentWeaponType and statistics accordingly
void Player::changeWeaponAndStatistics() {
	if (m_currentWeaponType != getEntity().getWeapon().type()) {
		m_currentWeaponType = getEntity().getWeapon().type();

		m_maxHp = Helper::getMaxHPBasedOnWeaponLevel(m_currentWeaponType);
		heal();

		m_maxXp = Helper::getMaxXPBasedOnWeaponLevel(m_currentWeaponType);
		m_xp = 0;

		m_speed = Helper::getSpeedBasedOnWeaponLevel(m_currentWeaponType);
	}
}