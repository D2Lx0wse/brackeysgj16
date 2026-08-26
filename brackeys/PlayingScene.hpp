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
	
	constexpr static float s_xpBarWidth{ Constants::g_ScreenWidth / 2.0f };
	constexpr static float s_xpBarHeight{50.0f};
	constexpr static float s_xpBarBtmDistance{10.0f};
	constexpr static float s_hpBarWidth{ 50.0f };
	constexpr static float s_hpBarHeight{ Constants::g_ScreenHeight / 2.0f };
	constexpr static float s_hpBarSideDistance{ 10.0f };


	PlayingScene();

	// Main loop methods
	void handleInput();
	SceneTypes logic(Scenes& scenes);
	void render();

	// Readies/closes scene
	void init();
	void exit();

private:
	void keepPlayerInBounds();

	void keepCameraInBounds();

	Font m_font{};
	Camera2D m_camera{ };
	/*
	Brackeys2DTexture m_test{};
	float m_testRot{};
	Entity m_testEntity;*/

	Player m_player;

	Brackeys2DTexture m_background;

	Vector2 xpBackgroundPos{};
	Vector2 xpBackgroundSize{};
	Vector2 xpBackgroundInnerPos{};
	Vector2 xpBackgroundInnerSize{};
	float xpBarLength{};

	Vector2 hpBackgroundPos{};
	Vector2 hpBackgroundSize{};
	Vector2 hpBackgroundInnerPos{};
	Vector2 hpBackgroundInnerSize{};
	float hpBarLength{};

	void renderWorld(Camera2D& camera);
	void renderUI();
	void initUI();
};
