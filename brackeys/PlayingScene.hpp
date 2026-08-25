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

	constexpr float m_SceneWidth{};
	constexpr float m_SceneHeight{};

	Player m_player;

	void renderWorld(Camera2D& camera);
	void renderUI();
};
