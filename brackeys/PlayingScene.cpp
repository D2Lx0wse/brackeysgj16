#include "PlayingScene.hpp"
#include "Brackeys2DTexture.hpp"
#include "Scenes.hpp"
#include "Vector2Overloads.hpp"
#include "Random.h"

//this is so sad
#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

const std::vector<Rectangle> PlayingScene::s_UpgradeSlotOutlines{ Rectangle{s_UpgradeBoxPosition.x + (s_UpgradeBoxSize.x / 100.0f) * 2.5f,
																			s_UpgradeBoxPosition.y + (s_UpgradeBoxSize.y / 100.0f) * 15.0f,
																			s_UpgradeSlotSize.x, s_UpgradeSlotSize.y },
																Rectangle{	s_UpgradeBoxPosition.x + (s_UpgradeBoxSize.x / 100.0f) * 7.5f + s_UpgradeSlotSize.x,
																			s_UpgradeBoxPosition.y + (s_UpgradeBoxSize.y / 100.0f) * 15.0f,
																			s_UpgradeSlotSize.x, s_UpgradeSlotSize.y }
															};

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
	, m_enemies{ {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} } // Number of enemies is a placeholder
	, m_choseLeftUpgradeSlot{ false }
	, m_choseRightUpgradeSlot{ false }
{
}

void PlayingScene::handleInput() {
	m_player.takeInput(m_camera);

	for (auto& enemy : m_enemies)
		enemy.generateInput(m_player.getEntity().getPosition());

	if (m_isInDeathScreen) {
		const Vector2 mousePosition{ GetMousePosition() };
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f }, Rectangle{ m_deathScreenButton.textPosition().x, m_deathScreenButton.textPosition().y, m_deathScreenButton.textSize().x, m_deathScreenButton.textSize().y }))
			m_nextScene = SceneTypes::MainMenu;
	}

	
	if (m_isInUpgradeScreen) {
		const Vector2 mousePosition{ GetMousePosition() };
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionRecs(	Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
								s_UpgradeSlotOutlines[0]
			))
			m_choseLeftUpgradeSlot = true;
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionRecs(Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
				s_UpgradeSlotOutlines[1]
			))
			m_choseRightUpgradeSlot = true;

	}

#ifdef _DEBUG
	if (IsKeyPressed(KEY_T)) {
		int enemiesAliveCounter{ 20 };
		for (const auto& enemy : m_enemies)
			if (enemy.isDead())
				--enemiesAliveCounter;
		std::cout << "Enemies alive: " << enemiesAliveCounter << '\n';
	}

	if (IsKeyPressed(KEY_L))
		m_player.decreaseHP(50);

	if (IsKeyPressed(KEY_U))
		m_player.increaseXP(50);

	if (IsKeyPressed(KEY_Q)) {
		m_enemies[0].kill();
		//m_enemies[1].kill();
	}

	if (IsKeyPressed(KEY_Z)) {
		std::cout << m_player.getHP() << '/' << m_player.getMaxHP() << '\n';
		std::cout << m_player.getXP() << '/' << m_player.getMaxXP() << '\n';
	}

#endif
}
SceneTypes PlayingScene::logic(Scenes& scenes) {
	bool areAllEnemiesDead{ true };
	for (const auto& enemy : m_enemies)
		areAllEnemiesDead = enemy.isDead();

	if (areAllEnemiesDead) {
#ifdef _DEBUG
		std::cout << "You win!\n";
#endif
		m_nextScene = SceneTypes::MainMenu;
	}
	if (m_nextScene != SceneTypes::MaxValue) {
		initNextScene(m_nextScene, scenes);

		exit();

		return m_nextScene;
	}

	if (m_player.getHP() <= 0 && !m_player.isDead()) {
		m_player.death();
		m_isInDeathScreen = true;
	}

	// If player isn't at the max level and has reached max xp, ready the upgrade screen
	if (m_player.getXP() >= m_player.getMaxXP() && !m_player.getEntity().isWeaponAtMaxLevel()) {
		m_isInUpgradeScreen = true;

		// Based on weapon chose, change the weapon to that and reset the upgrade values
		if (m_choseLeftUpgradeSlot) {
			m_isInUpgradeScreen = false;
			m_choseLeftUpgradeSlot = false;

			switch (m_player.getEntity().getWeapon().type()) {
			case Weapon::Fist_1:
				m_player.getEntity().setWeapon(Weapon::Sword_2A);
				break;
			case Weapon::Sword_2A:
				m_player.getEntity().setWeapon(Weapon::Sword_3A);
				break;
			case Weapon::Wand_2B:
				m_player.getEntity().setWeapon(Weapon::Wand_3C);
				break;
			default: break;
			}
			
			// Kept as comment in case it is needed
			/*m_player.think(); */
		}
		else if (m_choseRightUpgradeSlot) {
			m_isInUpgradeScreen = false;
			m_choseRightUpgradeSlot = false;

			switch (m_player.getEntity().getWeapon().type()) {
			case Weapon::Fist_1:
				m_player.getEntity().setWeapon(Weapon::Wand_2B);
				break;
			case Weapon::Sword_2A:
				m_player.getEntity().setWeapon(Weapon::Sword_3B);
				break;
			case Weapon::Wand_2B:
				m_player.getEntity().setWeapon(Weapon::Wand_3D);
				break;
			default: break;
			}

			/*m_player.think(); */
		}

		// If nothing was chosen yet, return so the rest of the code isn't ran
		else
			return SceneTypes::Playing;
	}

	m_player.think(m_enemies);

	
	for (auto& enemy : m_enemies) {
		// If enemy should be dead but the flag hasn't been set yet, call the death member function to render the enemy dead and give xp to the player
		if (enemy.getHP() <= 0 && !enemy.isDead()) {
			enemy.death();
			m_player.increaseXP(enemy.dropXP());
		}
		// Otherwise do as normal
		else
			enemy.think(m_player);
	}

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

	if (m_isInUpgradeScreen)
		renderUpgrade();

	if (m_isInDeathScreen)
		renderDeathScreen();

	EndDrawing();
}

// Readies/closes scene
void PlayingScene::init() {
	*this = PlayingScene{};

	m_isInUpgradeScreen = false;
	m_isInDeathScreen = false;

	m_choseLeftUpgradeSlot = false;
	m_choseRightUpgradeSlot = false;

	m_font = GetFontDefault();
	m_camera = Camera2D{ Vector2{0.0f,0.0f }, Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, 0.0f, 1.0f };
	/*
	m_test.loadFromFile("assets/images/player_vert.png");
	m_testEntity = Entity{ Vector2{Constants::g_ScreenWidth / 2, Constants::g_ScreenHeight / 2}, "assets/images/player_horiz.png", "assets/images/player_vert.png" };
	m_testEntity.reloadTextures();*/

	m_player.init();

	//const std::vector<Vector2> enemyPositions{ Vector2{1.0f, 1.0f}, { 200.0f, 150.0f } };
	Vector2 enemyPositionsRandom{};
	//assert(enemyPositions.size() == m_enemies.size() && "Error: There aren't as many enemies as there are positions for them.\n");
	m_enemies.clear();
	for (unsigned int i{ 0 }; i < 20u; ++i) {
		enemyPositionsRandom = Vector2{ static_cast<float>(Random::get(0, static_cast<int>(s_SceneWidth))), static_cast<float>(Random::get(0, static_cast<int>(s_SceneHeight))) };
		m_enemies.push_back(Enemy{});
		m_enemies[i].init(enemyPositionsRandom);
	}

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

void PlayingScene::renderUpgrade() {
	static std::vector<Brackeys2DTexture> weaponIcons{ {}, {} };
	std::vector<Vector2> weaponIconPositions{ {}, {} };

	// Initial render of the main brown upgrade box with the outline
	DrawRectangle(static_cast<int>(s_UpgradeBoxPosition.x), static_cast<int>(s_UpgradeBoxPosition.y), static_cast<int>(s_UpgradeBoxSize.x), static_cast<int>(s_UpgradeBoxSize.y), DARKBROWN);
	DrawRectangleLinesEx(Rectangle{ s_UpgradeBoxPosition.x, s_UpgradeBoxPosition.y, s_UpgradeBoxSize.x, s_UpgradeBoxSize.y }, 4.0f, Constants::g_DARKRED);


	// Gets info on the upgrades based on current weapon
	// This not being static worsens performance but fixes a bug.
	// The bug: if it's static, the value doesn't reset, this causes text to not reappear for the first upgrade when you restart the game
	Weapon::Type currentWeaponType{ Weapon::MaxType };
	if (currentWeaponType != m_player.getEntity().getWeapon().type()) {
		currentWeaponType = m_player.getEntity().getWeapon().type();

		switch (currentWeaponType) {
		case Weapon::Fist_1:
			m_upgradeSlotTitles[0].setText("Sword");
			m_upgradeSlotTitles[1].setText("Staff");

			m_upgradeSlotDescriptions[0].setText("This sword can\ndeal insane damage!");
			m_upgradeSlotDescriptions[1].setText("Get ready to throw\nenormous spells!");

			weaponIcons[0].loadFromFile("assets/images/sword_2a.png");
			weaponIcons[1].loadFromFile("assets/images/staff_2b.png");
			break;
		case Weapon::Sword_2A:
			m_upgradeSlotTitles[0].setText("Super Sword");
			m_upgradeSlotTitles[1].setText("Magic Sword");

			m_upgradeSlotDescriptions[0].setText("Strike with\nunimaginable force!");
			m_upgradeSlotDescriptions[1].setText("Super fast and\nfrequent projectiles!");

			weaponIcons[0].loadFromFile("assets/images/sword_3a.png");
			weaponIcons[1].loadFromFile("assets/images/sword_3b.png");
			break;
		case Weapon::Wand_2B:
			m_upgradeSlotTitles[0].setText("Super Staff");
			m_upgradeSlotTitles[1].setText("Fire Staff");

			m_upgradeSlotDescriptions[0].setText("Totally not the\nsame thing\nbut bigger!");
			m_upgradeSlotDescriptions[1].setText("Evaporate your\nenemies with a\nsuper long-range\nblast!");

			weaponIcons[0].loadFromFile("assets/images/staff_3c.png");
			weaponIcons[1].loadFromFile("assets/images/staff_3d.png");
			break;
		default: break;
		}
	}

	// Sets attributes of various elements to change their look
	m_upgradeBoxTitle.setPosition(Vector2{ (Constants::g_ScreenWidth - m_upgradeBoxTitle.textSize().x) / 2.0f, s_UpgradeBoxPosition.y + (s_UpgradeBoxSize.y / 100.0f) * 2.5f });
	m_upgradeBoxTitle.setFontSize(Constants::g_FontSize64, m_font);
	m_upgradeBoxTitle.setColor(Constants::g_DARKRED);

	std::vector<Color> upgradeSlotOutlineColors{ {}, {} };
	const Vector2 weaponIconSize{ weaponIcons[0].width() * Constants::g_ScalingSize / 2.5f, weaponIcons[0].height() * Constants::g_ScalingSize / 2.5f };
	for (unsigned int i{ 0 }; i < 2; ++i) {
		upgradeSlotOutlineColors[i] = BLACK;

		m_upgradeSlotTitles[i].setFontSize(40.0f, m_font);
		m_upgradeSlotTitles[i].setColor(BLACK);

		m_upgradeSlotDescriptions[i].setFontSize(24.0f, m_font);
		m_upgradeSlotDescriptions[i].setColor(BLACK);

		m_upgradeSlotTitles[i].setPosition(Vector2{ s_UpgradeSlotOutlines[i].x + (s_UpgradeSlotOutlines[i].width - m_upgradeSlotTitles[i].textSize().x) / 2, s_UpgradeSlotOutlines[i].y + s_UpgradeSlotOutlines[i].height / 2.0f });

		m_upgradeSlotDescriptions[i].setPosition(Vector2{ s_UpgradeSlotOutlines[i].x + (s_UpgradeSlotOutlines[i].width - m_upgradeSlotDescriptions[i].textSize().x) / 2, m_upgradeSlotTitles[i].textPosition().y + m_upgradeSlotTitles[i].textSize().y + m_upgradeSlotTitles[i].textSize().y / 2.0f });

		weaponIconPositions[i].x = s_UpgradeSlotOutlines[i].x + (s_UpgradeSlotOutlines[i].width - weaponIconSize.x) / 2;
		weaponIconPositions[i].y = s_UpgradeSlotOutlines[i].y + (s_UpgradeSlotOutlines[i].width / 100.0f) * 5.0f;
	}

	// Make outlines and text white on hover
	for (unsigned int i{ 0 }; i < 2; ++i) {
		Vector2 mousePosition{ GetMousePosition() };

		if (CheckCollisionRecs(Rectangle{ mousePosition.x, mousePosition.y, 0.0f, 0.0f }, s_UpgradeSlotOutlines[i])) {
			upgradeSlotOutlineColors[i] = WHITE;
			m_upgradeSlotTitles[i].setColor(WHITE);
			m_upgradeSlotDescriptions[i].setColor(WHITE);
		}
	}

	// Renders
	m_upgradeBoxTitle.render(m_font);
	for (unsigned int i{ 0 }; i < 2; ++i) {
		DrawRectangleLinesEx(s_UpgradeSlotOutlines[i], 4.0f, upgradeSlotOutlineColors[i]);

		m_upgradeSlotTitles[i].render(m_font);

		m_upgradeSlotDescriptions[i].render(m_font);

		weaponIcons[i].render(weaponIconPositions[i], weaponIconSize);
	}
}

void PlayingScene::renderDeathScreen() {
	// Get flavor text based on weapon you died with
	const std::vector<std::string_view> flavorTexts{
		"Might want to invest in a weapon! :)",														// Fists
		"It's at least stronger than before ;)", "Expected more? :O", "It's better than nothing! :D",// Swords
		"It gets bigger! ;)", "Not big enough? :O", "It's longer than slashes! :D",					// Wands
		"...How? o_O"																				// Placeholder
	};
	m_deathScreenFlavor.setText(flavorTexts[m_player.getEntity().getWeapon().type()]);
	m_deathScreenFlavor.setPosition(Vector2{ (Constants::g_ScreenWidth - m_deathScreenFlavor.textSize().x) / 2.0f, (Constants::g_ScreenHeight / 100.0f) * 33.3f * 1.625f });

	DrawRectangle(0, 0, Constants::g_ScreenWidth, Constants::g_ScreenHeight, RED);

	const Vector2 mousePosition{ GetMousePosition() };
	if (CheckCollisionRecs(Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f }, Rectangle{ m_deathScreenButton.textPosition().x, m_deathScreenButton.textPosition().y, m_deathScreenButton.textSize().x, m_deathScreenButton.textSize().y }))
		m_deathScreenButton.setColor(WHITE);
	else
		m_deathScreenButton.setColor(BLACK);

	m_deathScreenButton.render(m_font);

	m_deathScreenFlavor.render(m_font);

	m_deathScreenTitle.render(m_font);
}

void PlayingScene::initUI() {
	m_xpBackgroundPos = { (Constants::g_ScreenWidth - s_xpBarWidth) / 2,
						Constants::g_ScreenHeight - (s_xpBarHeight + s_xpBarBtmDistance) };
	m_xpBackgroundSize = { s_xpBarWidth , s_xpBarHeight };
	m_xpBackgroundInnerPos = { m_xpBackgroundPos + Vector2{Constants::g_ScalingSize, Constants::g_ScalingSize} };
	m_xpBackgroundInnerSize = { m_xpBackgroundSize - Vector2{Constants::g_ScalingSize * 2, Constants::g_ScalingSize * 2} };

	m_xpBarTitle.setText("XP");
	m_xpBarTitle.setColor(ORANGE);
	m_xpBarTitle.setFontSize(40.0f, GetFontDefault());
	m_xpBarTitle.setPosition(m_xpBackgroundPos + Vector2{ m_xpBackgroundSize.x - m_xpBarTitle.textSize().x, -m_xpBarTitle.spacing()-m_xpBarTitle.textSize().y });

	m_xpBarValue.setColor(ORANGE);
	m_xpBarValue.setFontSize(40.0f, GetFontDefault());

	m_hpBackgroundPos = { s_hpBarSideDistance, (Constants::g_ScreenHeight - s_hpBarHeight) / 2 };
	m_hpBackgroundSize = { s_hpBarWidth , s_hpBarHeight };
	m_hpBackgroundInnerPos = { m_hpBackgroundPos + Vector2{Constants::g_ScalingSize, Constants::g_ScalingSize} };
	m_hpBackgroundInnerSize = { m_hpBackgroundSize - Vector2{Constants::g_ScalingSize * 2, Constants::g_ScalingSize * 2} };

	m_hpBarTitle.setText("HP");
	m_hpBarTitle.setColor(RED);
	m_hpBarTitle.setFontSize(40.0f, GetFontDefault());
	m_hpBarTitle.setPosition(Vector2 {s_hpBarSideDistance, m_hpBackgroundPos.y-m_hpBarTitle.spacing()-m_hpBarTitle.textSize().y});
	
	m_hpBarValue.setColor(RED);
	m_hpBarValue.setFontSize(40.0f, GetFontDefault());
	m_hpBarValue.setPosition(Vector2{ s_hpBarSideDistance, m_hpBackgroundPos.y + m_hpBackgroundSize.y + m_hpBarValue.spacing() + m_hpBarValue.textSize().y/2 });

	m_upgradeBoxTitle.setColor(RED);
	const Vector2 upgradeBoxTitlePosition{ (Constants::g_ScreenWidth - m_upgradeBoxTitle.textSize().x) / 2.0f, s_UpgradeBoxPosition.y + (s_UpgradeBoxSize.y / 100.0f) * 2.5f };
	m_upgradeBoxTitle.setPosition(upgradeBoxTitlePosition);


	// Death screen init
	m_deathScreenButton.setText("Go back to the main menu");
	m_deathScreenButton.setFontSize(Constants::g_FontSize64 * 0.75f, m_font);
	m_deathScreenButton.setColor(BLACK);
	m_deathScreenButton.setPosition(Vector2{ (Constants::g_ScreenWidth - m_deathScreenButton.textSize().x) / 2.0f, (Constants::g_ScreenHeight / 100.0f) * 66.7f });

	m_deathScreenFlavor.setFontSize(Constants::g_FontSize64 * 0.5f, m_font);
	m_deathScreenFlavor.setColor(Constants::g_DARKRED);
	
	m_deathScreenTitle.setText("You died.");
	m_deathScreenTitle.setFontSize(Constants::g_FontSize64 * 1.5f, m_font);
	m_deathScreenTitle.setColor(WHITE);
	m_deathScreenTitle.setPosition(Vector2{ (Constants::g_ScreenWidth - m_deathScreenTitle.textSize().x) / 2.0f, (Constants::g_ScreenHeight / 100.0f) * 33.3f });
}

void PlayingScene::renderUI() {
	// XP bar
	m_xpBarLength = m_player.getXP() / static_cast<float>(m_player.getMaxXP()) *m_xpBackgroundInnerSize.x;
	DrawRectangleV(m_xpBackgroundPos, m_xpBackgroundSize, ORANGE);
	DrawRectangleV(m_xpBackgroundInnerPos, m_xpBackgroundInnerSize, GRAY);
	DrawRectangleV(m_xpBackgroundInnerPos, Vector2{ m_xpBarLength, m_xpBackgroundInnerSize.y }, YELLOW);
	m_xpBarTitle.render(GetFontDefault());
	std::string xpString{ std::to_string(m_player.getXP()) + "/" + std::to_string(m_player.getMaxXP()) };
	m_xpBarValue.setText(xpString);
	m_xpBarValue.setPosition(m_xpBackgroundPos + Vector2{ 0.0f, -m_xpBarTitle.spacing() - m_xpBarTitle.textSize().y });
	m_xpBarValue.render(GetFontDefault());

	// HP bar
	//m_hpBarLength = m_player.getXP() / static_cast<float>(m_player.getMaxXP()) * m_xpBackgroundInnerSize.x;
	m_hpBarLength = m_player.getHP() / static_cast<float>(m_player.getMaxHP()) * m_hpBackgroundInnerSize.y;
	DrawRectangleV(m_hpBackgroundPos, m_hpBackgroundSize, Constants::g_DARKRED);
	DrawRectangleV(m_hpBackgroundInnerPos, m_hpBackgroundInnerSize, GRAY);
	// To-Do (Polish): Make it start from the bottom (requires math to change pos and size)
	DrawRectangleV(m_hpBackgroundInnerPos, Vector2{m_hpBackgroundInnerSize.x, m_hpBarLength}, RED);
	m_hpBarTitle.render(GetFontDefault());
	std::string hpString{ std::to_string(m_player.getHP()) + "/\n" + std::to_string(m_player.getMaxHP()) };
	m_hpBarValue.setText(hpString);
	m_hpBarValue.render(GetFontDefault());
}