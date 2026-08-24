#pragma once

#include "MainMenuScene.hpp"
#include "PlayingScene.hpp"
#include "SceneTypes.hpp"

struct Scenes {
	MainMenuScene mainMenu{};
	PlayingScene playing{};
};

void initNextScene(SceneTypes nextScene, Scenes& scenes);