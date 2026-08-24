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
	Entity(Vector2 position, std::string_view path_horiz, std::string_view path_vert, Direction dir = up);
	~Entity();
	void Render();
	void Move(Vector2 vector);
	void Move(float vectorX, float vectorY);

private:
	Vector2 m_position{};
	Brackeys2DTexture m_textureHoriz{};
	Brackeys2DTexture m_textureVert{};
	Direction m_direction{};

	
	

	
};

