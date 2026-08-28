#include "Projectile.hpp"
#include <iostream>

void Projectile::init(Vector2 direction, float degrees, Entity* owner, Data projectileData) {
	if (owner == nullptr) {
		std::cerr << "Projectile with no owner! Oh no! \n";
		return;
	}
	m_owner = owner;
	m_data = projectileData;
	m_degrees = degrees;
	m_direction = direction;

	m_texture.loadFromFile(m_data.texturePath);

	m_hits.clear();

	m_isAlive = true;
	std::cout << "projectile is initted and alive! \n";
}

void Projectile::calc() {

}