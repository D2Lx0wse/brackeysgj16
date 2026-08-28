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
		std::string_view texturePath;
		float lifetime;
		//hit box type?????
	};
public:

	Projectile() {};
	

	void calc();
	void init(Vector2 direction, float degrees, Entity* owner, Data projectileData);

private:

	Vector2 m_direction{};
	float m_degrees{};
	Entity* m_owner{nullptr};
	Data m_data{};

	bool m_isAlive{false};
	std::vector<Entity*> m_hits{nullptr};
	Brackeys2DTexture m_texture{};

	//hitbox stuff here

};

