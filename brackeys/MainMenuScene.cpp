#pragma once

#include "MainMenuScene.hpp"
#include <iostream>

MainMenuScene::MainMenuScene()
	: m_sceneWidth{ Constants::g_ScreenWidth }
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
		std::cout << "Mouse collision with title screen.\n";
}

void MainMenuScene::logic() {}

void MainMenuScene::render() {
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	m_titleTexture.render((Constants::g_ScreenWidth - m_titleTexture.width()) / 2.0f, (m_sceneHeight / 100.0f) * 5.0f);

	float fontSize{ 64.0f };
	float fontSpacing{ fontSize / 10.0f };
	for (unsigned int i{ 0 }; i < m_menuOptionsText.size(); ++i) {
		Vector2 textSize{ MeasureTextEx(m_font, m_menuOptionsText[i].data(), fontSize, fontSpacing) };
		Vector2 textLocation{ (Constants::g_ScreenWidth - textSize.x) / 2.0f, ((Constants::g_ScreenHeight - textSize.y) / 2.0f) + fontSize * i };

		DrawTextEx(m_font, m_menuOptionsText[i].data(), textLocation, fontSize, fontSpacing, BLACK);
	}

	EndDrawing();
}

void MainMenuScene::init() {
	constexpr std::string_view titleImageFilePath{ "assets/images/title.png" };
	m_titleTexture.loadFromFile(titleImageFilePath.data());

	m_font = GetFontDefault();
}

void MainMenuScene::exit() {
	m_titleTexture.exit();

	m_font = Font{};
}