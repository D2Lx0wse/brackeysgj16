#include "Weapon.hpp"

#include <assert.h>

const std::vector<int> Weapon::s_WeaponDamages{
	1,			// Fist
	3, 5, 4,	// Swords
	2, 4, 3,	// Wands
	1			// Placeholder
};

const std::vector<std::string_view> Weapon::s_TextureFilepaths{ {
	"assets/images/weapon_placeholder.png",			// Fist
	"", "", "", // Swords
	"", "", "", // Wands
	"assets/images/weapon_placeholder.png"	// Placeholder
} };


Weapon::Weapon()
	: m_type{ Type::Fist_1 }
	, m_weaponDamage{}
	, m_currentTexture{}
{
	load();
}

void Weapon::setWeapon(Weapon::Type weaponType) {
	if (m_type != weaponType) {
		m_type = weaponType;
		load();
	}
}


void Weapon::load() {
	assert(s_TextureFilepaths.size() - 1 == Type::MaxType && "Error: s_TextureFilepaths doesn't have as many file paths as there are weapon types\n");
	assert(s_WeaponDamages.size() - 1 == Type::MaxType && "Error: s_WeaponDamages doesn't have as many damage values as there are weapon types\n");

	m_weaponDamage = s_WeaponDamages[m_type];
		
	m_currentTexture.loadFromFile(Weapon::s_TextureFilepaths[m_type]);
}