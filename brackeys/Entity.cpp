#include "Entity.hpp"
#include <string_view>
#include <iostream>
#include <cmath>

#include "Vector2Overloads.hpp"

void Entity::Render() {
	switch (m_direction) {
	case up:
		m_textureVert.render(m_position, Vector2{}, 180.f);
		return;
	case right:
		m_textureHoriz.render(m_position, Vector2{ -m_textureHoriz.width(),0 });
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
	if (vector == Vector2{ 0.0f, 0.0f })
		return;

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
		if (vector.y < 0) {
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

void Entity::setRadius(float radius) {
	m_radius = std::abs(radius);
}

Circle Entity::getCircle() {
	return Circle(getPosition(), getRadius());
}

Entity::Entity(Vector2 position, std::string_view path_horiz, std::string_view path_vert, Direction dir, float radius)
	:m_position{ position }, m_direction{ dir }, m_textureHorizPath{ path_horiz }, m_textureVertPath{ path_vert }
{
	m_textureHoriz.loadFromFile(path_horiz);
	m_textureVert.loadFromFile(path_vert);
	setRadius(radius);
}

Entity::~Entity()
{
}