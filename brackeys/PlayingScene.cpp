#include "PlayingScene.hpp"
#include "Brackeys2DTexture.hpp"
#include "Scenes.hpp"
#include "Vector2Overloads.hpp"

//this is so sad
#include <iostream>

#include <cmath>
#include <cassert>

// Keeps player character in bounds of the level
void PlayingScene::keepEntityInBounds(Entity& entity) {
	if (entity.getPosition().x < 0.0f)
		entity.setPosition(Vector2{ 0.0f, entity.getPosition().y });
	else if (entity.getPosition().x + entity.getRadius() * 2.0f > s_SceneWidth)
		entity.setPosition(Vector2{ s_SceneWidth - entity.getRadius() * 2.0f, entity.getPosition().y });

	if (entity.getPosition().y < 0.0f)
		entity.setPosition(Vector2{ entity.getPosition().x, 0.0f });
	else if (entity.getPosition().y + entity.getRadius() * 2.0f > s_SceneHeight)
		entity.setPosition(Vector2{ entity.getPosition().x, s_SceneHeight - entity.getRadius() * 2.0f });
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

bool PlayingScene::areTwoEntitiesNear(Vector2 position1, Vector2 position2, const Vector2& distanceBetween) {
	// Centers the positions
	position1 += {m_player.getEntity().getRadius() * Constants::g_ScalingSize, m_player.getEntity().getRadius()* Constants::g_ScalingSize };
	position2 += {m_player.getEntity().getRadius()* Constants::g_ScalingSize, m_player.getEntity().getRadius()* Constants::g_ScalingSize };

	return (std::abs(position1.x - position2.x) < distanceBetween.x && std::abs(position1.y - position2.y) < distanceBetween.y);
}

PlayingScene::PlayingScene()
	: m_font{}
	, m_camera{}
	, m_background{}
	, m_player{}
	, m_enemies{ {}, {} } // Number of enemies is a placeholder
{
}

void PlayingScene::handleInput() {
	m_player.takeInput(m_camera);

	for (auto& enemy : m_enemies)
		enemy.generateInput();
}
SceneTypes PlayingScene::logic([[maybe_unused]]Scenes& scene) {
	m_player.think();
	
	for (auto& enemy : m_enemies)
		enemy.think();

	keepEntityInBounds(m_player.getEntity());
	
	for (auto& enemy : m_enemies)
		keepEntityInBounds(enemy.entity());
	
	constexpr Vector2 ScreenSize{ static_cast<float>(Constants::g_ScreenWidth) / 2.0f, static_cast<float>(Constants::g_ScreenHeight) / 2.0f };
	for (auto& enemy : m_enemies) {
		bool areNear{ areTwoEntitiesNear(m_player.getEntity().getPosition(), enemy.entity().getPosition(), ScreenSize) };
		if (areNear)
			enemy.setMode(Enemy::Attacking);
		else
			enemy.setMode(Enemy::Roaming);
	}

	// Center camera on player character
	m_camera.target = Vector2{ m_player.getEntity().getPosition().x - Constants::g_ScreenWidth / 2.0f + m_player.getEntity().getRadius(), m_player.getEntity().getPosition().y - Constants::g_ScreenHeight / 2.0f + m_player.getEntity().getRadius() };
	
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
	//m_player = Player{ Entity{Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png"}};
	//m_player = Player{ Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2} };
	m_player.getEntity().setPosition(Vector2{ Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2 });
	m_player.getEntity().setRadius(8.0f);

	m_player.getEntity().setTextures("assets/images/player_horiz.png", "assets/images/player_vert.png");
	m_player.getEntity().reloadTextures();

	const std::vector<Vector2> enemyPositions{ Vector2{1.0f, 1.0f}, { 200.0f, 150.0f } };
	assert(enemyPositions.size() == m_enemies.size() && "Error: There aren't as many enemies as there are positions for them.\n");
	for (unsigned int i{ 0 }; i < m_enemies.size(); ++i) {
		m_enemies[i].init(enemyPositions[i]);
	}

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

	for (auto& enemy : m_enemies)
		enemy.render();

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