#include "Weapon.hpp"

#include <assert.h>

const std::vector<int> Weapon::s_WeaponDamages{
	1,			// Fist
	3, 5, 4,	// Swords
	2, 4, 3,	// Staffs
	1			// Placeholder
};

const std::vector<std::string_view> Weapon::s_TextureFilepaths{ {
	"",			// Fist
	"assets/images/sword.png", "", "", // Swords
	"assets/images/magic_staff.png", "", "", // Staffs
	"assets/images/weapon_placeholder.png"	// Placeholder
} };

const std::vector<std::string_view> Weapon::s_AttackTextureFilepaths{
	"",											// Fist
	"assets/images/sword_swing.png", "", "",	// Swords
	"assets/images/magic_pellet.png", "", "",	// Staffs
	"",											// Placeholder
};

Weapon::Weapon()
	: m_type{ Type::Sword_2A }
	, m_weaponDamage{}
	, m_currentTexture{}
{
}

void Weapon::setWeapon(Weapon::Type weaponType) {
	if (m_type != weaponType) {
		m_type = weaponType;
		load();
	}
}


void Weapon::load() {
	assert(s_WeaponDamages.size() - 1 == Type::MaxType && "Error: s_WeaponDamages doesn't have as many damage values as there are weapon types\n");
	assert(s_TextureFilepaths.size() - 1 == Type::MaxType && "Error: s_TextureFilepaths doesn't have as many file paths as there are weapon types\n");
	assert(s_AttackTextureFilepaths.size() - 1 == Type::MaxType && "Error: s_AttackTextureFilepaths doesn't have as many file paths as there are weapon types\n");	

	m_weaponDamage = s_WeaponDamages[m_type];
		
	m_currentTexture.loadFromFile(Weapon::s_TextureFilepaths[m_type]);

	m_currentAttackTexture.loadFromFile(Weapon::s_AttackTextureFilepaths[m_type]);
}