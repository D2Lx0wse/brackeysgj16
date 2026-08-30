#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "Scenes.hpp"
#include "SceneTypes.hpp"

int main() {
	InitWindow(Constants::g_ScreenWidth, Constants::g_ScreenHeight, Constants::g_DefaultTitle.data());

	SetTargetFPS(60);

	Image windowIcon{ LoadImage("assets/images/player_vert.png") };
	SetWindowIcon(windowIcon);

	Scenes scenes{};
	SceneTypes currentScene{ SceneTypes::MainMenu };

	switch (currentScene) {
	case SceneTypes::MainMenu: scenes.mainMenu.init(); break;

	case SceneTypes::Credits: scenes.credits.init(); break;

	case SceneTypes::Playing: scenes.playing.init(); break;

	case SceneTypes::Tutorial: scenes.tutorial.init(); break;

	default: break;
	}

	while (!scenes.quitGame) {
		if (WindowShouldClose())
			scenes.quitGame = true;

		switch (currentScene) {
		case SceneTypes::MainMenu: scenes.mainMenu.handleInput(); break;

		case SceneTypes::Credits: scenes.credits.handleInput(); break;

		case SceneTypes::Playing: scenes.playing.handleInput(); break;

		case SceneTypes::Tutorial: scenes.tutorial.handleInput(); break;

		default: break;
		}

		switch (currentScene) {
		case SceneTypes::MainMenu: currentScene = scenes.mainMenu.logic(scenes); break;

		case SceneTypes::Credits: currentScene = scenes.credits.logic(scenes);  break;

		case SceneTypes::Playing: currentScene = scenes.playing.logic(scenes); break;

		case SceneTypes::Tutorial: currentScene = scenes.tutorial.logic(scenes); break;

		default: break;
		}

		switch (currentScene) {
		case SceneTypes::MainMenu: scenes.mainMenu.render(); break;

		case SceneTypes::Credits: scenes.credits.render(); break;

		case SceneTypes::Playing: scenes.playing.render(); break;

		case SceneTypes::Tutorial: scenes.tutorial.render(); break;

		default: break;
		}
	}

	switch (currentScene) {
	case SceneTypes::MainMenu: scenes.mainMenu.exit(); break;

	case SceneTypes::Credits: scenes.credits.exit(); break;

	case SceneTypes::Playing: scenes.playing.exit(); break;

	case SceneTypes::Tutorial: scenes.tutorial.exit(); break;

	default: break;
	}

	CloseWindow();
	UnloadImage(windowIcon);

	return 0;
}
