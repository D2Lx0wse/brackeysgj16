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
	Camera2D m_camera{ };
	Brackeys2DTexture m_test{};
	float m_testRot{};

	void renderWorld(Camera2D& camera);
	void renderUI();
};
