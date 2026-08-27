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
	void generateInput();
	void think();
	void render();

	void init(Vector2 position);

	// Getters / Setters
	void setPosition(Vector2 position) { m_entity.setPosition(position); }
	
	void setMode(Mode mode);
	Mode mode() const { return m_mode; }
	Entity& entity() { return m_entity; } // Careful use
private:
	// The mode dictates how the AI will behave
	Mode m_mode{};

	Entity m_entity{};

	// Enemy speed
	float m_speed{ Constants::g_SpeedSlow };

	// Used for movement
	Vector2 m_inputVector{};
	Vector2 m_movementVector{};

	// Paths to the enemies sprites
	constexpr static std::string_view s_HorizontalTexture{ "assets/images/enemy_horiz.png" };
	constexpr static std::string_view s_VerticalTexture{ "assets/images/enemy_vert.png" };

	double m_clock{ -1.0 };
	double m_randomDuration{};
};