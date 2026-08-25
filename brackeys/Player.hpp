#pragma once
#include "raylib.h"
#include "Entity.hpp"

class Player
{
public:
	Player();
	~Player();

	//getters
	Entity getEntity() const { return m_entity; }

private:
	Entity m_entity;
	int m_xp;
	int m_level;
	int m_hp;

};

