#pragma once

#include <string_view>
#include "Entity.hpp"
#include "Constants.hpp"

class Enemy {
public:
	enum Mode {
		Roaming,
		Attacking, 
		MaxModes,
	};

public:
	// Constructor
	Enemy();
	Enemy(const Enemy& enemy);

	// Enemy input will be generated using a PRNG library, think and render will be very similar to Player
	void generateInput();
	void think();
	void render();

	void init(Vector2 position);

	// Getters / Setters
	void setPosition(Vector2 position) { m_entity.setPosition(position); }
	
	void setMode(Mode mode) { m_mode = mode; }
	Mode mode() const { return m_mode; }
	Entity& entity() { return m_entity; } // Careful use
private:
	Mode m_mode{};

	Entity m_entity{};

	// Taken from player
	float m_speed{ Constants::g_SpeedSlow };

	Vector2 m_inputVector{};
	Vector2 m_movementVector{};

	constexpr static std::string_view s_HorizontalTexture{ "assets/images/enemy_horiz.png" };
	constexpr static std::string_view s_VerticalTexture{ "assets/images/enemy_vert.png" };
};