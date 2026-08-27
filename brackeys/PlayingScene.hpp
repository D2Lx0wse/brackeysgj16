#pragma once
#include "raylib.h"
#include "Brackeys2DTexture.hpp"
#include "Constants.hpp"
#include "SceneTypes.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

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
	void keepEntityInBounds(Entity& entity);

	void keepCameraInBounds();

	Font m_font{};
	Camera2D m_camera{ };
	/*
	Brackeys2DTexture m_test{};
	float m_testRot{};
	Entity m_testEntity;*/

	Player m_player;

	std::vector<Enemy> m_enemies{};

	Brackeys2DTexture m_background;

	Vector2 m_xpBackgroundPos{};
	Vector2 m_xpBackgroundSize{};
	Vector2 m_xpBackgroundInnerPos{};
	Vector2 m_xpBackgroundInnerSize{};
	float m_xpBarLength{};

	Vector2 m_hpBackgroundPos{};
	Vector2 m_hpBackgroundSize{};
	Vector2 m_hpBackgroundInnerPos{};
	Vector2 m_hpBackgroundInnerSize{};
	float m_hpBarLength{};

	void renderWorld(Camera2D& camera);
	void renderUI();
	void initUI();
};
