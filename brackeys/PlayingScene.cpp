#include "PlayingScene.hpp"
#include "Brackeys2DTexture.hpp"
#include "Scenes.hpp"

//this is so sad
#include <iostream>

PlayingScene::PlayingScene()
	: m_font{}
	, m_camera{}
	, m_background{}
{
}

void PlayingScene::handleInput() {
	m_player.takeInput();
}
SceneTypes PlayingScene::logic([[maybe_unused]]Scenes& scene) {
	m_player.think();

	// Keeps player character in bounds of the level
	if (m_player.getEntity().getPosition().x < 0.0f)
		m_player.getEntity().setPosition(Vector2{ 0.0f, m_player.getEntity().getPosition().y });
	else if (m_player.getEntity().getPosition().x + m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f > s_SceneWidth)
		m_player.getEntity().setPosition(Vector2{ s_SceneWidth - m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f, m_player.getEntity().getPosition().y});

	if (m_player.getEntity().getPosition().y < 0.0f)
		m_player.getEntity().setPosition(Vector2{ m_player.getEntity().getPosition().x, 0.0f });
	else if (m_player.getEntity().getPosition().y + m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f > s_SceneHeight)
		m_player.getEntity().setPosition(Vector2{ m_player.getEntity().getPosition().x, s_SceneHeight - m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f });

	// Center camera on player character
	m_camera.target = Vector2{ m_player.getEntity().getPosition().x - Constants::g_ScreenWidth / 2.0f + m_player.getEntity().getRadius() * Constants::g_ScalingSize, m_player.getEntity().getPosition().y - Constants::g_ScreenHeight / 2.0f + m_player.getEntity().getRadius() * Constants::g_ScalingSize };
	
	// Keeps camera in bounds of the level
	if (m_camera.target.x < 0.0f)
		m_camera.target.x = 0.0f;
	else if (m_camera.target.x + Constants::g_ScreenWidth > s_SceneWidth)
		m_camera.target.x = s_SceneWidth - Constants::g_ScreenWidth;

	if (m_camera.target.y < 0.0f)
		m_camera.target.y = 0.0f;
	else if (m_camera.target.y + Constants::g_ScreenHeight > s_SceneHeight)
		m_camera.target.y = s_SceneHeight - Constants::g_ScreenHeight;

	return SceneTypes::Playing;
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
	*this = PlayingScene{};

	m_font = GetFontDefault();
	m_camera = Camera2D{ Vector2{0.0f,0.0f }, Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, 0.0f, 1.0f };
	/*
	m_test.loadFromFile("assets/images/player_vert.png");
	m_testEntity = Entity{ Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png" };
	m_testEntity.reloadTextures();*/

	m_player = Player{ Entity{Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png"} };
	m_player.getEntity().setRadius(8.0f);
	m_player.getEntity().reloadTextures();

	std::cout << "player birth" << std::endl;

	m_background.loadFromFile("assets/images/grass.png");
}
void PlayingScene::exit() {

}

//rendering stuff
void PlayingScene::renderWorld(Camera2D& camera) {
	BeginMode2D(camera);
	
#if _DEBUG
	int counter{};
#endif
	
	constexpr float epsilon{ 0.001f }; // Used for rendering the grass texture specificially as many times as it needed, avoiding float accuracy issues
	for (float i{ 0.0f }; i <= (s_SceneWidth - m_background.width() + epsilon); i += m_background.width()) {
		for (float j{ 0.0f }; j <= (s_SceneHeight - m_background.height() + epsilon); j += m_background.height()) {
			m_background.render(Vector2{ i, j });
#if _DEBUG
			++counter;
#endif
		}
	}
#if _DEBUG
	std::cout << "Rendered background " << counter << " times, should be 25 times\n";
#endif // DEBUG

	

	//lil test teehee
	DrawRectangle(Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2, 10, 10, BLACK);
	//m_test.render(Constants::g_ScreenWidth/2, Constants::g_ScreenHeight / 2, {}, m_testRot);
	m_player.render();
	EndMode2D();
}

void PlayingScene::renderUI() {
	//m_test.render(0.0f, 0.0f);
}