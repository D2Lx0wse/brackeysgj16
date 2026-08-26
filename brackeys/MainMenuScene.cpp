#pragma once

#include "MainMenuScene.hpp"
#include "Scenes.hpp" // To make InitNextScene() visible
#include "Helper.hpp"

#include <iostream>

MainMenuScene::MainMenuScene()
	: m_nextScene{ SceneTypes::MaxValue }
	, m_quitGame{ false }
	, m_sceneWidth{ Constants::g_ScreenWidth }
	, m_sceneHeight{ Constants::g_ScreenHeight }
	, m_titleTexture{}
	, m_font{}
{
}

void MainMenuScene::handleInput() {
	const Vector2 mousePosition{ GetMousePosition() };

	if (IsMouseButtonPressed(0)) {
		if (CheckCollisionRecs(
			Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
			Rectangle{ m_menuOptions[0].textPosition().x, m_menuOptions[0].textPosition().y, m_menuOptions[0].textSize().x, m_menuOptions[0].textSize().y })
			)
			m_nextScene = SceneTypes::Playing;


		if (CheckCollisionRecs(
			Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
			Rectangle{ m_menuOptions[1].textPosition().x, m_menuOptions[1].textPosition().y, m_menuOptions[1].textSize().x, m_menuOptions[1].textSize().y })
		)
			m_nextScene = SceneTypes::Credits;

		if (CheckCollisionRecs(
			Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
			Rectangle{ m_menuOptions[2].textPosition().x, m_menuOptions[2].textPosition().y, m_menuOptions[2].textSize().x, m_menuOptions[2].textSize().y })
			)
			m_quitGame = true;
	}

	for (auto& menuOption : m_menuOptions) {
		if (CheckCollisionRecs(
			Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
			Rectangle{ menuOption.textPosition().x, menuOption.textPosition().y, menuOption.textSize().x, menuOption.textSize().y })
			)
			menuOption.setColor(RAYWHITE);
		else if (!Helper::isColorTheSameBetween(menuOption.color(), BLACK))
			menuOption.setColor(BLACK);
	}
}

SceneTypes MainMenuScene::logic(Scenes& scenes) {
	if (m_nextScene != SceneTypes::MaxValue) {
		initNextScene(m_nextScene, scenes);

		exit();

		return m_nextScene;
	}

	if (m_quitGame)
		scenes.quitGame = true;

	return s_Scene;
}

void MainMenuScene::render() {
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	m_titleTexture.render((Constants::g_ScreenWidth - m_titleTexture.width()) / 2.0f, (m_sceneHeight / 100.0f) * 5.0f);

	for (const auto& menuOption : m_menuOptions) {
		menuOption.render(m_font);
	}

	HideCursor();
	m_cursorTexture.render(GetMousePosition(), Vector2{24.0f, 24.0f});

	EndDrawing();
}

void MainMenuScene::init() {
	*this = MainMenuScene{};

	m_cursorTexture.loadFromFile("assets/images/cursor.png");

	constexpr std::string_view titleImageFilePath{ "assets/images/title.png" };
	m_titleTexture.loadFromFile(titleImageFilePath.data());

	m_font = GetFontDefault();

	m_menuOptions = {
		{ "Start Game", m_font }, { "Credits", m_font }, { "Close Game", m_font }
	};

	float verticalSpaceBetweenOptions{ Constants::g_FontSize64 / 2.0f };
	for (auto& menuOption : m_menuOptions) {
		menuOption.setPosition(
			Vector2{ (Constants::g_ScreenWidth - menuOption.textSize().x) / 2.0f, (Constants::g_ScreenHeight - menuOption.textSize().y) / 2.0f + verticalSpaceBetweenOptions }
		);

		verticalSpaceBetweenOptions += Constants::g_FontSize64;
	}
}

void MainMenuScene::exit() {
	m_titleTexture.exit();

	m_cursorTexture.exit();
	ShowCursor();

	m_font = Font{};
}