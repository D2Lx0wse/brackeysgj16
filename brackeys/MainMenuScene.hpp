#pragma once
#include <string_view>
#include <vector>

#include "raylib.h"

#include "Constants.hpp"
#include "Brackeys2DTexture.hpp"
#include "BrackeysText.hpp"
#include "SceneTypes.hpp"

#include "Scenes.hpp"

class MainMenuScene {
public:
	static constexpr SceneTypes s_Scene{ SceneTypes::MainMenu };

	MainMenuScene();

	// Main loop methods
	void handleInput();
	SceneTypes logic(Scenes& scenes);
	void render();

	// Readies/closes scene
	void init();
	void exit();
private:
	SceneTypes m_nextScene{ SceneTypes::MaxValue };

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