#pragma once
#include "raylib.h"
#include "Brackeys2DTexture.hpp"
#include "Constants.hpp"

class PlayingScene
{
public:
	PlayingScene();

	// Main loop methods
	void handleInput();
	void logic();
	void render();

	// Readies/closes scene
	void init();
	void exit();

private:
	Font m_font{};
	Camera2D m_camera{ Vector2{ Constants::g_ScreenWidth / 2.0f, Constants::g_ScreenHeight / 2.0f }, Vector2{0.0f, 0.0f}, 0.0f, 1.0f };
	Brackeys2DTexture m_test{};

	void renderWorld(Camera2D& camera);
	void renderUI();
};
