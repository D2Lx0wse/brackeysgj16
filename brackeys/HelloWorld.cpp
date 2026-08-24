#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "Scenes.hpp"
#include "SceneTypes.hpp"

int main() {
	InitWindow(Constants::g_ScreenWidth, Constants::g_ScreenHeight, Constants::g_DefaultTitle.data());

	SetTargetFPS(60);

	Scenes scenes{};
	SceneTypes currentScene{ SceneTypes::MainMenu };

	int choice{};
	std::cout << "Choose scene: ";
	std::cin >> choice;

	if (choice == 1)
		currentScene = SceneTypes::MainMenu;
	else if (choice == 2)
		currentScene = SceneTypes::Playing;

	switch (currentScene) {
	case SceneTypes::MainMenu: scenes.mainMenu.init(); break;

	case SceneTypes::Credits:  break;

	case SceneTypes::Playing: scenes.playing.init(); break;

	default: break;
	}

	while (!WindowShouldClose()) {
		switch (currentScene) {
		case SceneTypes::MainMenu: scenes.mainMenu.handleInput(); break;

		case SceneTypes::Credits:  break;

		case SceneTypes::Playing: scenes.playing.handleInput(); break;

		default: break;
		}

		switch (currentScene) {
		case SceneTypes::MainMenu: currentScene = scenes.mainMenu.logic(scenes); break;

		case SceneTypes::Credits:  break;

		case SceneTypes::Playing: scenes.playing.logic(); break;

		default: break;
		}

		switch (currentScene) {
		case SceneTypes::MainMenu: scenes.mainMenu.render(); break;

		case SceneTypes::Credits:  break;

		case SceneTypes::Playing: scenes.playing.render(); break;

		default: break;
		}
	}

	switch (currentScene) {
	case SceneTypes::MainMenu: scenes.mainMenu.exit(); break;

	case SceneTypes::Credits:  break;

	case SceneTypes::Playing: scenes.playing.exit(); break;

	default: break;
	}

	return 0;
}
