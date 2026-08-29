#pragma once

#include "MainMenuScene.hpp"
#include "CreditsScene.hpp"
#include "PlayingScene.hpp"
#include "TutorialScene.hpp"
#include "SceneTypes.hpp"

struct Scenes {
	MainMenuScene mainMenu{};
	CreditsScene credits{};
	PlayingScene playing{};
	TutorialScene tutorial{};

	bool quitGame{ false };
};

void initNextScene(SceneTypes nextScene, Scenes& scenes);