#pragma once

#include <string_view>

#include "Entity.hpp"
#include "Constants.hpp"

class Enemy {
public:
	// Used for deciding how the AI should behave. Roaming is for when the enemy is searching another opponent. Attacking is for when an enemy is attacking a foe
	enum Mode {
		Roaming,
		Attacking,
		MaxModes,
	};

public:
	// Constructors
	Enemy();
	Enemy(const Enemy& enemy);

	// Enemy input will be generated using a PRNG library, think and render will be very similar to Player
	// generateInput takes in the player position to determine how the enemy should move when in attack mode
	void generateInput(const Vector2& playerPosition);
	void think();
	void render();

	void init(Vector2 position);

	// Death operations, such as setting m_isDead to true and the position to outside the scene
	void death();

	// Getters / Setters
	void setPosition(Vector2 position) { m_entity.setPosition(position); }

	void setMode(Mode mode);
	Mode mode() const { return m_mode; }
	
	Entity& entity() { return m_entity; } // Careful use

	int getHP() const { return m_hp; }
	int getMaxHP() const { return m_maxHp; }
	bool isDead() const { return m_isDead; }

	// Give out XP based on current weapon type
	int dropXP();

	void heal() { m_hp = m_maxHp; }
	void kill() { m_hp = 0; }
	void decreaseHP(int hp);

private:
	void changeWeaponAndStatistics();

	// The mode dictates how the AI will behave
	Mode m_mode{};

	Entity m_entity{};

	Weapon::Type m_currentWeaponType{ Weapon::MaxType };

	// Hp and speed technically don't need to have initializaiton values since they are assigned values properly in Enemy::init()
	int m_hp{ 0 };
	int m_maxHp{ 100 };

	bool m_isDead{ false };

	// Enemy speed
	float m_speed{ Constants::g_SpeedSlow };

	float m_aimDegrees{};

	// Used for movement
	Vector2 m_inputVector{};
	Vector2 m_movementVector{};

	Vector2 m_aimVector{};

	bool m_willAttack{ false };

	// Paths to the enemies sprites
	constexpr static std::string_view s_HorizontalTexture{ "assets/images/enemy_horiz.png" };
	constexpr static std::string_view s_VerticalTexture{ "assets/images/enemy_vert.png" };

	double m_clock{ -1.0 };
	double m_randomDuration{};
};