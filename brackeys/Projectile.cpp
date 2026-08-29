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

void Projectile::calc(std::vector<Enemy>& enemies) {
	
	if (m_data.lifetime < 0.f){	
		m_isAlive = false; return;}
	m_data.lifetime -= GetFrameTime();

	m_position += 
		m_direction * Constants::g_ScalingSize * GetFrameTime() * m_data.speed;

	for (auto& enemy : enemies) {
		if (CheckCollisionCircles(m_position, m_texture.width() / 2.f, enemy.entity().getPosition(), enemy.entity().getCircle().radius)) {
			bool haveWeAlreadyHitThis{ false };
			for (Entity*& hit : m_hits) {
				if (hit == &enemy.entity()) {
					haveWeAlreadyHitThis = true;
				}
			}
			if (haveWeAlreadyHitThis) { continue; }
			else {
				std::cout << "Enemy hit!\n ";
				enemy.decreaseHP(static_cast<int>(m_data.damage));
				m_hits.push_back(&enemy.entity());
			}
		}
	}
}

void Projectile::render() {
	m_texture.render(m_position +
		(m_direction * 8.0f * Constants::g_ScalingSize * 3.0f) - //g_scaling size *8.0f is a made up value, but it works
		Vector2{ (
			m_texture.width()
			- (8.0f * Constants::g_ScalingSize * 2.0f)
			) / 2.0f
		,	(m_texture.height()
			- (8.0f * Constants::g_ScalingSize * 2.0f)
			) / 2.0f
		}
	, Vector2{}, m_degrees);
}