#include <iostream>
#include "raylib.h"

int main() {
	constexpr int screenWidth{800};
	constexpr int screenHeigth{600};

	InitWindow(screenWidth, screenHeigth, "brackeys 2026 2");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {



		BeginDrawing();

		ClearBackground(RAYWHITE);

		EndDrawing();
	}


	return 0;
}
