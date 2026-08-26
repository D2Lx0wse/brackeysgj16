#include "PlayingScene.hpp"
#include "Brackeys2DTexture.hpp"
#include "Scenes.hpp"
#include "Vector2Overloads.hpp"

//this is so sad
#include <iostream>

// Keeps player character in bounds of the level
void PlayingScene::keepPlayerInBounds() {
	if (m_player.getEntity().getPosition().x < 0.0f)
		m_player.getEntity().setPosition(Vector2{ 0.0f, m_player.getEntity().getPosition().y });
	else if (m_player.getEntity().getPosition().x + m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f > s_SceneWidth)
		m_player.getEntity().setPosition(Vector2{ s_SceneWidth - m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f, m_player.getEntity().getPosition().y });

	if (m_player.getEntity().getPosition().y < 0.0f)
		m_player.getEntity().setPosition(Vector2{ m_player.getEntity().getPosition().x, 0.0f });
	else if (m_player.getEntity().getPosition().y + m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f > s_SceneHeight)
		m_player.getEntity().setPosition(Vector2{ m_player.getEntity().getPosition().x, s_SceneHeight - m_player.getEntity().getRadius() * Constants::g_ScalingSize * 2.0f });
}

// Keeps camera in bounds of the level
void PlayingScene::keepCameraInBounds() {
	if (m_camera.target.x < 0.0f)
		m_camera.target.x = 0.0f;
	else if (m_camera.target.x + Constants::g_ScreenWidth > s_SceneWidth)
		m_camera.target.x = s_SceneWidth - Constants::g_ScreenWidth;

	if (m_camera.target.y < 0.0f)
		m_camera.target.y = 0.0f;
	else if (m_camera.target.y + Constants::g_ScreenHeight > s_SceneHeight)
		m_camera.target.y = s_SceneHeight - Constants::g_ScreenHeight;
}

PlayingScene::PlayingScene()
	: m_font{}
	, m_camera{}
	, m_background{}{
}

void PlayingScene::handleInput() {
	m_player.takeInput();
}
SceneTypes PlayingScene::logic([[maybe_unused]]Scenes& scene) {
	m_player.think();
	
	keepPlayerInBounds();
	
	// Center camera on player character
	m_camera.target = Vector2{ m_player.getEntity().getPosition().x - Constants::g_ScreenWidth / 2.0f + m_player.getEntity().getRadius() * Constants::g_ScalingSize, m_player.getEntity().getPosition().y - Constants::g_ScreenHeight / 2.0f + m_player.getEntity().getRadius() * Constants::g_ScalingSize };
	
	keepCameraInBounds();

	return SceneTypes::Playing;
}
void PlayingScene::render() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	renderWorld(m_camera);

	renderUI();
#if _DEBUG
	std::cout << "FPS: " << GetFPS() << '\n';
#endif

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

	// The line below may pose some trouble
	m_player = Player{ Entity{Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png"} };
	m_player.getEntity().setPosition(Vector2{ Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2 });
	m_player.getEntity().setTextures("assets/images/player_horiz.png", "assets/images/player_vert.png");
	//m_player.getEntity().getWeapon().texture().loadFromFile(Weapon::s_TextureFilepaths[m_player.getEntity().getWeapon().type()]);

	m_player.getEntity().setRadius(8.0f);
	m_player.getEntity().reloadTextures();

	std::cout << "player birth" << std::endl;

	m_background.loadFromFile("assets/images/grass.png");
	initUI();
}
void PlayingScene::exit() {
	
}

//rendering stuff
void PlayingScene::renderWorld(Camera2D& camera) {
	BeginMode2D(camera);
	
	constexpr float epsilon{ 0.001f }; // Used for rendering the grass texture specificially as many times as it needed, avoiding float accuracy issues
	for (float i{ 0.0f }; i <= (s_SceneWidth - m_background.width() + epsilon); i += m_background.width()) {
		for (float j{ 0.0f }; j <= (s_SceneHeight - m_background.height() + epsilon); j += m_background.height()) {
			m_background.render(Vector2{ i, j });
		}
	}

	//lil test teehee
	DrawRectangle(Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2, 10, 10, BLACK);
	//m_test.render(Constants::g_ScreenWidth/2, Constants::g_ScreenHeight / 2, {}, m_testRot);

	m_player.render();

	EndMode2D();
}

void PlayingScene::initUI() {
	m_xpBackgroundPos = { (Constants::g_ScreenWidth - s_xpBarWidth) / 2,
						Constants::g_ScreenHeight - (s_xpBarHeight + s_xpBarBtmDistance) };
	m_xpBackgroundSize = { s_xpBarWidth , s_xpBarHeight };
	m_xpBackgroundInnerPos = { m_xpBackgroundPos + Vector2{Constants::g_ScalingSize, Constants::g_ScalingSize} };
	m_xpBackgroundInnerSize = { m_xpBackgroundSize - Vector2{Constants::g_ScalingSize * 2, Constants::g_ScalingSize * 2} };

	m_hpBackgroundPos = { s_hpBarSideDistance, (Constants::g_ScreenHeight - s_hpBarHeight) / 2 };
	m_hpBackgroundSize = { s_hpBarWidth , s_hpBarHeight };
	m_hpBackgroundInnerPos = { m_hpBackgroundPos + Vector2{Constants::g_ScalingSize, Constants::g_ScalingSize} };
	m_hpBackgroundInnerSize = { m_hpBackgroundSize - Vector2{Constants::g_ScalingSize * 2, Constants::g_ScalingSize * 2} };

}

void PlayingScene::renderUI() {
	// XP bar
	m_xpBarLength = m_player.getXP() / static_cast<float>(m_player.getMaxXP()) *m_xpBackgroundInnerSize.x;
	DrawRectangleV(m_xpBackgroundPos, m_xpBackgroundSize, ORANGE);
	DrawRectangleV(m_xpBackgroundInnerPos, m_xpBackgroundInnerSize, GRAY);
	DrawRectangleV(m_xpBackgroundInnerPos, Vector2{ m_xpBarLength, m_xpBackgroundInnerSize.y }, YELLOW);

	// HP bar
	//m_hpBarLength = m_player.getXP() / static_cast<float>(m_player.getMaxXP()) * m_xpBackgroundInnerSize.x;
	m_hpBarLength = m_player.getHP() / static_cast<float>(m_player.getMaxHP()) * m_hpBackgroundInnerSize.y;
	DrawRectangleV(m_hpBackgroundPos, m_hpBackgroundSize, Constants::g_DARKRED);
	DrawRectangleV(m_hpBackgroundInnerPos, m_hpBackgroundInnerSize, GRAY);
	// To-Do (Polish): Make it start from the bottom (requires math to change pos and size)
	DrawRectangleV(m_hpBackgroundInnerPos, Vector2{m_hpBackgroundInnerSize.x, m_hpBarLength}, RED);
}