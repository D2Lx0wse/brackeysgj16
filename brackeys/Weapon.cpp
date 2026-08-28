#include "Weapon.hpp"

#include <assert.h>

const std::vector<int> Weapon::s_WeaponDamages{
	1,			// Fist
	3, 5, 4,	// Swords
	2, 4, 3,	// Staffs
	1			// Placeholder
};

const std::vector<std::string_view> Weapon::s_TextureFilepaths{ {
	"",																							// Fist
	"assets/images/sword_2a.png", "assets/images/sword_3a.png", "assets/images/sword_3b.png",	// Swords
	"assets/images/staff_2b.png", "assets/images/staff_3c.png", "assets/images/staff_3d.png",	// Staffs
	"assets/images/weapon_placeholder.png"														// Placeholder
} };

const std::vector<std::string_view> Weapon::s_AttackTextureFilepaths{
	"assets/images/punch_blue_1.png",																// Fist
	"assets/images/slash_2a.png", "assets/images/slash_3a.png", "assets/images/slash_3b.png",		// Swords
	"assets/images/pellet_2b.png", "assets/images/pellet_3c.png", "assets/images/pellet_3d.png",	// Staffs
	"assets/images/attack_placeholder.png",															// Placeholder
	"assets/images/pellet_3b.png",																	// Magic sword pellet
};

const std::vector<double> Weapon::s_AttackDurations{
	0.5, // Fists, Swords, placeholder
	3.0, // Staffs
};

Weapon::Weapon()
	: m_type{}
	, m_weaponDamage{}
	, m_currentTexture{}
	, m_attackDuration{}
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
	//assert(s_AttackTextureFilepaths.size() - 1 == Type::MaxType && "Error: s_AttackTextureFilepaths doesn't have as many file paths as there are weapon types\n");	

	m_weaponDamage = s_WeaponDamages[m_type];
		
	m_currentTexture.loadFromFile(Weapon::s_TextureFilepaths[m_type]);

	m_currentAttackTexture.loadFromFile(Weapon::s_AttackTextureFilepaths[m_type]);

	switch (m_type) {
	case Type::Fist_1:

	case Type::Sword_2A:
	case Type::Sword_3A:
	case Type::Sword_3B:

	case Type::MaxType:
		m_attackDuration = s_AttackDurations[0];
		break;

	case Type::Wand_2B:
	case Type::Wand_3C:
	case Type::Wand_3D:
		m_attackDuration = s_AttackDurations[1];
		break;

	default: break;
	}
}