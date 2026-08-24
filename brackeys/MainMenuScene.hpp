#pragma once
#include <string_view>
#include <vector>

#include "raylib.h"

#include "Constants.hpp"
#include "Brackeys2DTexture.hpp"
#include "BrackeysText.hpp"

class MainMenuScene {
public:
	MainMenuScene();

	// Main loop methods
	void handleInput();
	void logic();
	void render();

	// Readies/closes scene
	void init();
	void exit();
private:
	// Scene size
	int m_sceneWidth{ Constants::g_ScreenWidth };
	int m_sceneHeight{ Constants::g_ScreenHeight };

	// Camera
	Camera2D m_camera{
		Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f}, 0.0f, 1.0f
	};

	// Assets (fonts, images, sounds, etc.)
	Brackeys2DTexture m_titleTexture{};

	Font m_font{ GetFontDefault() };

	std::vector<BrackeysText> m_menuOptions{};
};