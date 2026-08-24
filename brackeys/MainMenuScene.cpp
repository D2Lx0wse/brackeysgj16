#pragma once

#include "MainMenuScene.hpp"

#include <iostream>

MainMenuScene::MainMenuScene()
	: m_nextScene{ SceneTypes::MaxValue }
	, m_sceneWidth{ Constants::g_ScreenWidth }
	, m_sceneHeight{ Constants::g_ScreenHeight }
	, m_camera{}
	, m_titleTexture{}
	, m_font{}
{
	init();
}

void MainMenuScene::handleInput() {
	const Vector2 mousePosition{ GetMousePosition() };
	if (CheckCollisionRecs(
		Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
		Rectangle{ (Constants::g_ScreenWidth - m_titleTexture.width()) / 2.0f, (m_sceneHeight / 100.0f) * 5.0f,  m_titleTexture.width(), m_titleTexture.height() })
		)
		m_nextScene = SceneTypes::Playing;
}

SceneTypes MainMenuScene::logic(Scenes& scenes) {
	if (m_nextScene != SceneTypes::MaxValue) {
		initNextScene(m_nextScene, scenes);

		exit();

		return m_nextScene;
	}


	return s_Scene;
}

void MainMenuScene::render() {
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	m_titleTexture.render((Constants::g_ScreenWidth - m_titleTexture.width()) / 2.0f, (m_sceneHeight / 100.0f) * 5.0f);

	for (const auto& menuOption : m_menuOptions) {
		menuOption.render(m_font);
	}

	EndDrawing();
}

void MainMenuScene::init() {
	m_nextScene = SceneTypes::MaxValue;

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

	m_font = Font{};
}