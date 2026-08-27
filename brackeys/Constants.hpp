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

	constexpr Color g_DARKRED{ 100, 0, 0 ,255 };
}