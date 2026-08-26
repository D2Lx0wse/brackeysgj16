#pragma once
#include "raylib.h"
#include "Entity.hpp"

class Player
{
public:
	Player() = default;
	Player(Entity ent);
	~Player();

	void takeInput();
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
	int m_hp{};
	int m_maxHp{};

	float m_speed{ Constants::g_SpeedSlow };

	Vector2 m_inputVector{};
	Vector2 m_movementVector{};
};

