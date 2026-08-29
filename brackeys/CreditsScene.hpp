#pragma once

#include <vector>

#include "raylib.h"
#include "Brackeys2DTexture.hpp"
#include "Constants.hpp"
#include "BrackeysText.hpp"
#include "SceneTypes.hpp"

struct Scenes;

class CreditsScene {
public:
	static constexpr SceneTypes s_Scene{ SceneTypes::Credits };

	CreditsScene();

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

	// Assets
	Font m_font{ GetFontDefault() };

	BrackeysText m_creditsTitle{};

	std::vector<BrackeysText> m_credits{};

	BrackeysText m_goBackText{};

	Brackeys2DTexture m_cursorTexture{};
};