#pragma once
#include"raylib.h"
#include "Entity.hpp"
#include <vector>

class Projectile
{
public:
	struct Data
	{
		float speed;
		float damage;
		//hit box type?????
	};
public:



	Projectile() {};
	

	void calc();
	void init();

private:

	bool m_isAlive{false};
	Vector2 m_direction{};
	float m_degrees{};
	Entity* m_owner{nullptr};
	std::vector<Entity*> m_hits{nullptr};
	float m_lifetime{};
	Data m_data{};

	//hitbox stuff here

};

