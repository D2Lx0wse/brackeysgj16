#pragma once
#include "raylib.h"

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
};
