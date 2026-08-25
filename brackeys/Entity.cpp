#include "Entity.hpp"
#include <string_view>
#include <iostream>

void Entity::Render() {
	switch (m_direction) {
	case up:
		m_textureVert.render(m_position, Vector2{}, 180.f);
		return;
	case right:
		m_textureHoriz.render(m_position, Vector2{ -static_cast<float>(m_textureHoriz.texture().width),0 });
		return;
	case down:
		m_textureVert.render(m_position);
		return;
	case left:
		m_textureHoriz.render(m_position);
		return;
	default:
		std::cerr << "impossible direction!!!";
		return;
	}
}

void Entity::Move(float vectorX, float vectorY) {
	Move(Vector2{ vectorX, vectorY });
}

void Entity::Move(Vector2 vector) {
	m_position.x += vector.x;
	m_position.y += vector.y;
	if (std::abs(vector.x) > std::abs(vector.y)) {
		if (vector.x > 0) {
			m_direction = right;
		}
		else {
			m_direction = left;
		}
	}
	else {
		if (vector.y > 0) {
			m_direction = up;
		}
		else {
			m_direction = down;
		}
	}
}

void Entity::reloadTextures() {
	m_textureHoriz.loadFromFile(m_textureHorizPath);
	m_textureVert.loadFromFile(m_textureVertPath);
}

Entity::Entity(Vector2 position, std::string_view path_horiz, std::string_view path_vert, Direction dir)
	:m_position{ position }, m_direction{ dir }, m_textureHorizPath{ path_horiz }, m_textureVertPath{ path_vert }
{
	m_textureHoriz.loadFromFile(path_horiz);
	m_textureVert.loadFromFile(path_vert);
}

Entity::~Entity()
{
}