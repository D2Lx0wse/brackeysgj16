#pragma once
#include <string_view>

namespace Constants {
	constexpr int g_ScreenWidth{ 800 };
	constexpr int g_ScreenHeight{ 600 };
	constexpr std::string_view g_DefaultTitle{ "Brackeys game jam 2026.2" };

	constexpr float g_ScalingSize{ 5.0f }; // All textures size is multiplied by this value

	constexpr float g_FontSize64{ 64.0f };

	constexpr float g_SpeedSlow{ 100.0f };
	constexpr float g_SpeedMedium{ g_SpeedSlow * 1.5f };
	constexpr float g_SpeedFast{ g_SpeedMedium * 1.5f };
	constexpr float g_EnemySpeedMultiplier{ 0.9f };

	constexpr int g_HpLow{ 100 };
	constexpr int g_HpMedium{ g_HpLow * 2 };
	constexpr int g_HpHigh{ g_HpMedium * 2 };

	constexpr int g_XpLow{ 100 };
	constexpr int g_XpMedium{ g_XpLow * 3 };
	constexpr int g_XpHigh{ g_XpMedium * 3 };

	constexpr int g_EnemyAttackEffort{ 10 }; //every frame a number between -this and 1 is picked, if 1 enemy attack

	constexpr Color g_DARKRED{ 100, 0, 0 ,255 };
	constexpr Color g_QUARTERALPHA{ 255, 255, 255, 64 };
	constexpr Color g_FAKEFRIEND{ 99, 155, 255, 255 };
}