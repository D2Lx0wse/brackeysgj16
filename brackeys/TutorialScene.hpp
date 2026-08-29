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

	BrackeysText m_TutorialTitle{ "Tutorial!", m_font };

	BrackeysText m_TutorialText{ "- Move with WASD!\n- Aim and attack with the mouse!\n- Get upgrades as you defeat enemies!", m_font };

	BrackeysText m_tutorialButton{ "Play Game", m_font };
};