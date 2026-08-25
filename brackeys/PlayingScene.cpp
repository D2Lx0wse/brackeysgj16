#include "PlayingScene.hpp"
#include "Brackeys2DTexture.hpp"
#include "Scenes.hpp"

//this is so sad
#include <iostream>

PlayingScene::PlayingScene()
	: m_font{}
	, m_camera{}
	, m_test{}
{
}

void PlayingScene::handleInput() {
	if (IsKeyDown(KEY_W)){
		m_testEntity.Move({ 0.0f,-1.0f });
	}
	if (IsKeyDown(KEY_S)) {
		m_testEntity.Move({ 0.0f,1.0f });
	}
	if (IsKeyDown(KEY_A)) {
		m_testEntity.Move({ -1.0f, 0 });
	}
	if (IsKeyDown(KEY_D)) {
		m_testEntity.Move({ 1.0f, 0.0f });
	}
}
SceneTypes PlayingScene::logic([[maybe_unused]]Scenes& scene) {
	m_camera.target = Vector2{ 5.0f, 5.0f };
	
	return SceneTypes::Playing;
}
void PlayingScene::render() {

	m_testRot += 5.0f;

	BeginDrawing();

	ClearBackground(RAYWHITE);

	renderWorld(m_camera);

	renderUI();

	EndDrawing();

}

// Readies/closes scene
void PlayingScene::init() {
	*this = PlayingScene{};

	m_font = GetFontDefault();
	m_test.loadFromFile("assets/images/player_vert.png");
	m_camera = Camera2D{ Vector2{0.0f,0.0f }, Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, 0.0f, 1.0f };
	m_testEntity = Entity{ Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png" };
	m_testEntity.reloadTextures();
	std::cout << "entity birth" << std::endl;
}
void PlayingScene::exit() {

}

//rendering stuff
void PlayingScene::renderWorld(Camera2D& camera) {
	BeginMode2D(camera);

	//lil test teehee
	
	DrawRectangle(Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2, 10, 10, BLACK);
	//m_test.render(Constants::g_ScreenWidth/2, Constants::g_ScreenHeight / 2, {}, m_testRot);
	m_testEntity.Render();
	EndMode2D();
}

void PlayingScene::renderUI() {
	//m_test.render(0.0f, 0.0f);
}