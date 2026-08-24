#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "MainMenuScene.hpp"

class CreditsScene {


};

int main() {
	InitWindow(Constants::g_ScreenWidth, Constants::g_ScreenHeight, Constants::g_DefaultTitle.data());

	SetTargetFPS(60);

	MainMenuScene scene{};
	scene.init();

	while (!WindowShouldClose()) {
		// Handle input
		scene.handleInput();

		// Logic
		scene.logic();

		// Render
		scene.render();
	}

	scene.exit();

	return 0;
}
