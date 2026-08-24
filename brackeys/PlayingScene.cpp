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
}
void PlayingScene::exit() {

}

//rendering stuff
void PlayingScene::renderWorld(Camera2D& camera) {
	BeginMode2D(camera);

	//lil test teehee
	
	
	m_test.render(5.0f, 5.0f);
	EndMode2D();
}

void PlayingScene::renderUI() {

}