#pragma once
#include"raylib.h"
#include "Entity.hpp"
#include <vector>
#include <string_view>
#include "Enemy.hpp"
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
	

	void calc(std::vector<Enemy>& enemies);
	void init(Vector2 direction, float degrees, Entity* owner, Data projectileData, Vector2 position);
	void render();

	//getters and setter
	bool isAlive(){ return m_isAlive; }

private:
	Vector2 m_position{};
	Vector2 m_direction{};
	float m_degrees{};
	Entity* m_owner{nullptr};
	Data m_data{};


	bool m_isAlive{false};
	std::vector<Entity*> m_hits{nullptr};
	Brackeys2DTexture m_texture{};

	//hitbox stuff here

};

