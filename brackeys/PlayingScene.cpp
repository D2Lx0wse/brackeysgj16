#include "PlayingScene.hpp"
#include "Brackeys2DTexture.hpp"

PlayingScene::PlayingScene()
	: m_font{}
	, m_camera{}
	, m_test{}
{
}

void PlayingScene::handleInput() {

}
void PlayingScene::logic() {
	m_camera.target = Vector2{ 5.0f, 5.0f };
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
	m_font = GetFontDefault();
	m_test.loadFromFile("assets/images/player_vert.png");
	m_camera = Camera2D{ Vector2{0.0f,0.0f }, Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, 0.0f, 1.0f };
}
void PlayingScene::exit() {

}

//rendering stuff
void PlayingScene::renderWorld(Camera2D& camera) {
	BeginMode2D(camera);

	//lil test teehee
	
	DrawRectangle(Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2, 10, 10, BLACK);
	m_test.render(Constants::g_ScreenWidth/2, Constants::g_ScreenHeight / 2, {}, m_testRot);
	EndMode2D();
}

void PlayingScene::renderUI() {
	//m_test.render(0.0f, 0.0f);
}