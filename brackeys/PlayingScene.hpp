#pragma once
#include "raylib.h"
#include "Brackeys2DTexture.hpp"
#include "Constants.hpp"
#include "SceneTypes.hpp"
#include "Entity.hpp"
#include "Player.hpp"

struct Scenes;

class PlayingScene
{
public:
	static constexpr SceneTypes s_Scene{ SceneTypes::Playing };

	constexpr static float s_SceneWidth{ Constants::g_ScreenWidth * 4.0f };
	constexpr static float s_SceneHeight{ Constants::g_ScreenWidth * 4.0f  };

	PlayingScene();

	// Main loop methods
	void handleInput();
	SceneTypes logic(Scenes& scenes);
	void render();

	// Readies/closes scene
	void init();
	void exit();

private:
	Font m_font{};
	Camera2D m_camera{ };
	/*
	Brackeys2DTexture m_test{};
	float m_testRot{};
	Entity m_testEntity;*/

	Player m_player;

	void renderWorld(Camera2D& camera);
	void renderUI();
};
