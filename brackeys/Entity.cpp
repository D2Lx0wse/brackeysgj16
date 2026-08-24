#include "Entity.hpp"
#include <string_view>
#include <iostream>

void Entity::Render() {
	switch (m_direction) {
	case up:
		return;
	case right:
		return;
	case down:
		return;
	case left:
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

}

Entity::Entity(Vector2 position, std::string_view path_horiz, std::string_view path_vert, Direction dir)
	:m_position{position}, m_direction {dir}
{
	m_textureHoriz.loadFromFile(path_horiz);
	m_textureVert.loadFromFile(path_vert);
}

Entity::~Entity()
{
}