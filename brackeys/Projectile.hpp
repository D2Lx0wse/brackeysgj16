#pragma once
#include"raylib.h"
#include "Entity.hpp"
#include <vector>
#include <string_view>

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

	std::string_view m_texturePath{};
	Vector2 m_direction{};
	float m_degrees{};
	Entity* m_owner{nullptr};

	bool m_isAlive{false};
	std::vector<Entity*> m_hits{nullptr};
	float m_lifetime{};
	Data m_data{};
	
	Brackeys2DTexture m_texture{};

	//hitbox stuff here

};

