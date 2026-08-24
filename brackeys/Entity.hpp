#pragma once
#include "raylib.h"
#include "Brackeys2DTexture.hpp"

class Entity
{
private:
	enum Direction {
		up,
		right,
		down,
		left,
	};

public:
	Entity();
	~Entity();

private:
	Vector2 m_position{};
	Brackeys2DTexture m_texture{};
	Direction m_direction{};


	

	
};

Entity::Entity()
{
}

Entity::~Entity()
{
}