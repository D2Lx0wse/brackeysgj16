#pragma once

#include "MainMenuScene.hpp"
#include "CreditsScene.hpp"
#include "PlayingScene.hpp"
#include "SceneTypes.hpp"

struct Scenes {
	MainMenuScene mainMenu{};
	CreditsScene credits{};
	PlayingScene playing{};

	bool quitGame{ false };
};

void initNextScene(SceneTypes nextScene, Scenes& scenes);