#pragma once
#include"raylib.h"
#include "Entity.hpp"
#include <vector>

class Projectile
{
public:
	Projectile()=delete;
	

	void calc();
	void init();

private:
	float m_speed{};
	bool m_isAlive{};
	Vector2 m_direction{};
	float m_degrees{};
	Entity* m_owner{nullptr};
	std::vector<Entity*> m_hits{nullptr};
	float m_damage{};
	float m_lifetime{};

	//hitbox stuff here

};

