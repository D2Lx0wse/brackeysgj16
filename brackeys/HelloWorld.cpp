#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "MainMenuScene.hpp"

int main() {
	InitWindow(Constants::g_ScreenWidth, Constants::g_ScreenHeight, "brackeys 2026 2");

	SetTargetFPS(60);

	MainMenuScene scene{};
	scene.init();

	while (!WindowShouldClose()) {
		// Handle input
		// ...

		// Logic
		// ...

		// Render
		scene.render();
	}

	scene.exit();

	return 0;
}
