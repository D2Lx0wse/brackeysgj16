#pragma once
#include "raylib.h"
#include "Entity.hpp"

class Player
{
public:
	Player() = default;
	Player(Entity ent);
	Player(Vector2 position);
	~Player();

	void takeInput(const Camera2D& camera);
	void think();
	void render();

	//getters
	int getMaxXP(){ return m_maxXp; }
	int getXP() { return m_xp; }
	int getMaxHP() { return m_maxHp; }
	int getHP() { return m_hp; }

	//returns REFERENCE to player entity
	Entity& getEntity() { return m_entity; }

private:
	Entity m_entity;

	int m_xp{20};
	int m_maxXp{100};
	int m_level{};
	int m_hp{75};
	int m_maxHp{ 100 };

	float m_speed{ Constants::g_SpeedSlow };

	Vector2 m_inputVector{};
	Vector2 m_movementVector{};
	Vector2 m_aimVector{};

	bool m_willAttack{ false };

	constexpr static std::string_view s_HorizontalTexture{ "assets/images/player_horiz.png" };
	constexpr static std::string_view s_VerticalTexture{ "assets/images/player_vert.png" };
};

