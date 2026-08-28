#pragma once
#include "raylib.h"
#include "Entity.hpp"

class Player
{
public:
	Player() = default;
	~Player();

	void takeInput(const Camera2D& camera);
	void think();
	void render();
	void init();

	//getters
	int getMaxXP(){ return m_maxXp; }
	int getXP() { return m_xp; }
	int getMaxHP() { return m_maxHp; }
	int getHP() { return m_hp; }

	void heal() { m_hp = m_maxHp; }
	void kill() { m_hp = 0; }

	//returns REFERENCE to player entity
	Entity& getEntity() { return m_entity; }

private:
	void changeWeaponAndStatistics();

	Entity m_entity;

	Weapon::Type m_currentWeaponType{};

	// Default values for xp, hp and speed technically not needed since they get the correct values in Player::init()
	int m_xp{ 0 };
	int m_maxXp{ 100 };
	
	int m_hp{ 100 };
	int m_maxHp{ 100 };

	float m_speed{ Constants::g_SpeedSlow };
	float m_aimDegrees{};

	Vector2 m_inputVector{};
	Vector2 m_movementVector{};
	Vector2 m_aimVector{};

	bool m_willAttack{ false };

	Brackeys2DTexture m_arrow{};

	constexpr static std::string_view s_HorizontalTexture{ "assets/images/player_horiz.png" };
	constexpr static std::string_view s_VerticalTexture{ "assets/images/player_vert.png" };
	constexpr static std::string_view s_ArrowTexture{ "assets/images/arrow.png" };
};

