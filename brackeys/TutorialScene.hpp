#pragma once

#include "raylib.h"

#include "Constants.hpp"
#include "BrackeysText.hpp"
#include "SceneTypes.hpp"

struct Scenes;

class TutorialScene {
public:
	static constexpr SceneTypes s_Scene{ SceneTypes::Tutorial };

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

	BrackeysText m_TutorialTitle{ "placeholder tutorial title", m_font };

	BrackeysText m_TutorialText{ "placeholder tutorial text", m_font };

	BrackeysText m_tutorialButton{ "placeholder play button", m_font };
};