#include "Projectile.hpp"
#include "Constants.hpp"
#include "Vector2Overloads.hpp"
#include <iostream>

void Projectile::init(Vector2 direction, float degrees, Entity* owner, Data projectileData, Vector2 position) {
	if (owner == nullptr) {
		std::cerr << "Projectile with no owner! Oh no! \n";
		return;
	}
	m_owner = owner;
	m_data = projectileData;
	m_degrees = degrees;
	m_direction = direction;
	m_position = position;

	m_texture.loadFromFile(m_data.texturePath);

	m_hits.clear();

	m_isAlive = true;
	std::cout << "projectile is initted and alive! \n";
}

void Projectile::calc() {
	if (m_data.lifetime < 0.f){	
		m_isAlive = false; return;}
	m_position += 
		m_direction * Constants::g_ScalingSize * GetFrameTime() * m_data.speed;

}

void Projectile::render() {
	m_texture.render(m_position);
}