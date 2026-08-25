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

	//returns REFERENCE to player entity
	Entity& getEntity() { return m_entity; }

private:
	Entity m_entity;

	int m_xp{};
	int m_level{};
	int m_hp{};

	float m_speed{ Constants::g_SpeedSlow };

	Vector2 m_inputVector{};
	Vector2 m_movementVector{};
};

