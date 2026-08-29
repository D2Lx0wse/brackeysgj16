#include "TutorialScene.hpp"
#include "Scenes.hpp"
#include "Helper.hpp"

void TutorialScene::handleInput() {
	const Vector2 mousePosition{ GetMousePosition() };
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

		if (CheckCollisionRecs(
			Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
			Rectangle{ m_tutorialButton.textPosition().x, m_tutorialButton.textPosition().y, m_tutorialButton.textSize().x, m_tutorialButton.textSize().y })
			)
				m_nextScene = SceneTypes::Playing;
	}

	if (CheckCollisionRecs(
		Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
		Rectangle{ m_tutorialButton.textPosition().x, m_tutorialButton.textPosition().y, m_tutorialButton.textSize().x, m_tutorialButton.textSize().y })
		)
		m_tutorialButton.setColor(RAYWHITE);
	else if (!Helper::isColorTheSameBetween(m_tutorialButton.color(), BLACK))
		m_tutorialButton.setColor(BLACK);
}

SceneTypes TutorialScene::logic(Scenes& scenes) {
	if (m_nextScene != SceneTypes::MaxValue) {
		initNextScene(m_nextScene, scenes);

		exit();

		return m_nextScene;
	}

	return SceneTypes::Tutorial;
}

void TutorialScene::render() {
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	m_TutorialTitle.render(m_font);

	m_TutorialText.render(m_font);

	m_tutorialButton.render(m_font);

	EndDrawing();
}


void TutorialScene::init() {
	*this = TutorialScene();

	m_nextScene = SceneTypes::MaxValue;

	m_font = GetFontDefault();

	m_TutorialTitle.setText("Tutorial!");
	m_TutorialTitle.setColor(DARKBLUE);
	m_TutorialTitle.setFontSize(Constants::g_FontSize64 * 2.0f, m_font);

	m_TutorialText.setText("- Move with WASD!\n- Aim and attack with\nthe mouse!\n- Get upgrades as you\ndefeat enemies!");
	m_TutorialText.setColor(BLUE);
	m_TutorialText.setFontSize(Constants::g_FontSize64 * 0.8f, m_font);

	m_tutorialButton.setText("Play Game");
	m_tutorialButton.setColor(BLACK);
	m_tutorialButton.setFontSize(Constants::g_FontSize64, m_font);

	m_TutorialTitle.setPosition(Vector2{ (Constants::g_ScreenWidth - m_TutorialTitle.textSize().x) / 2.0f, (Constants::g_ScreenHeight / 100.0f) * 7.5f });
	m_TutorialText.setPosition(Vector2{ (Constants::g_ScreenWidth - m_TutorialText.textSize().x) / 2.0f, (Constants::g_ScreenHeight / 100.0f) * 32.5f });
	m_tutorialButton.setPosition(Vector2{ (Constants::g_ScreenWidth - m_tutorialButton.textSize().x) / 2.0f, (Constants::g_ScreenHeight / 100.0f) * 82.5f });
}

void TutorialScene::exit() {
	m_font = Font{};
}