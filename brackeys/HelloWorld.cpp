#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "MainMenuScene.hpp"
#include "PlayingScene.hpp"

int main() {
	InitWindow(Constants::g_ScreenWidth, Constants::g_ScreenHeight, Constants::g_DefaultTitle.data());

	SetTargetFPS(60);

	MainMenuScene mainMenuScene{};
	PlayingScene playingScene{};

	int choice{};
	std::cout << "Choose scene: ";
	std::cin >> choice;

	if (choice == 1)
		mainMenuScene.init();
	else if (choice == 2)
		playingScene.init();

	while (!WindowShouldClose()) {
		if (choice == 1) {
			// Handle input
			mainMenuScene.handleInput();

			// Logic
			mainMenuScene.logic();

			// Render
			mainMenuScene.render();
		}

		else if (choice == 2) {
			// Handle input
			playingScene.handleInput();

			// Logic
			playingScene.logic();

			// Render
			playingScene.render();
		}
	}

	if (choice == 1)
		mainMenuScene.exit();
	else if (choice == 2)
		playingScene.exit();

	return 0;
}
