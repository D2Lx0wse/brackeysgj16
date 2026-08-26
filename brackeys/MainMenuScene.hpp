#pragma once
#include <string_view>
#include <vector>

#include "raylib.h"

#include "Constants.hpp"
#include "Brackeys2DTexture.hpp"
#include "BrackeysText.hpp"
#include "SceneTypes.hpp"

struct Scenes; // Needed to make struct Scene in here work

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
	bool m_quitGame{ false };

	// Scene size
	int m_sceneWidth{ Constants::g_ScreenWidth };
	int m_sceneHeight{ Constants::g_ScreenHeight };

	// Assets (fonts, images, sounds, etc.)
	Brackeys2DTexture m_titleTexture{};

	Font m_font{ GetFontDefault() };

	std::vector<BrackeysText> m_menuOptions{};

	Brackeys2DTexture m_cursorTexture{};
};