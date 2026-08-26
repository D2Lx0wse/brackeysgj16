#pragma once

#include <vector>
#include <string_view>

#include "Brackeys2DTexture.hpp"

class Weapon {
public:
	enum Type {
		Fist_1,

		Sword_2A,
		Sword_3A,
		Sword_3B,

		Wand_2B,
		Wand_3C,
		Wand_3D,

		MaxType,
	};

public:
	// Information for all weapon types
	const static std::vector<int> s_WeaponDamages;
	const static std::vector<std::string_view> s_TextureFilepaths; // Defined in Weapons.cpp

	// Constructor. Calls load()
	Weapon();

	// Sets a new weapon based on the given type
	void setWeapon(Weapon::Type weaponType);

	// Getters
	Type type() const { return m_type; }
	int weaponDamage() const { return m_weaponDamage; }
	// Gives access to the private member
	Brackeys2DTexture& texture() { return m_currentTexture; } 

private:
	// Changes weapon based on m_type
	void load();

	Type m_type{ Type::Fist_1 };

	int m_weaponDamage{};

	Brackeys2DTexture m_currentTexture{};
};