#include "CreditsScene.hpp"
#include "Scenes.hpp"
#include "Helper.hpp"

CreditsScene::CreditsScene()
	: m_nextScene{ SceneTypes::MaxValue }
	, m_sceneWidth{ Constants::g_ScreenWidth }
	, m_sceneHeight{ Constants::g_ScreenHeight }
	, m_font{}
	, m_creditsTitle{}
	, m_credits{}
	, m_goBackText{}
{
}

void CreditsScene::handleInput() {
	const Vector2 mousePosition{ GetMousePosition() };

	if (IsMouseButtonPressed(0)) {

		if (CheckCollisionRecs(
			Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
			Rectangle{ m_goBackText.textPosition().x, m_goBackText.textPosition().y, m_goBackText.textSize().x, m_goBackText.textSize().y })
			)
			m_nextScene = SceneTypes::MainMenu;
	}

	if (CheckCollisionRecs(
		Rectangle{ mousePosition.x, mousePosition.y, 1.0f, 1.0f },
		Rectangle{ m_goBackText.textPosition().x, m_goBackText.textPosition().y, m_goBackText.textSize().x, m_goBackText.textSize().y })
		)
		m_goBackText.setColor(RAYWHITE);
	else if (!Helper::isColorTheSameBetween(m_goBackText.color(), BLACK))
		m_goBackText.setColor(BLACK);
}

SceneTypes CreditsScene::logic(Scenes& scenes) {
	if (m_nextScene != SceneTypes::MaxValue) {
		initNextScene(m_nextScene, scenes);

		exit();

		return m_nextScene;
	}

	return s_Scene;
}

void CreditsScene::render() {
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	m_creditsTitle.render(m_font);
	
	for (const auto& credit : m_credits)
		credit.render(m_font);

	m_goBackText.render(m_font);

	EndDrawing();
}

void CreditsScene::init() {
	*this = CreditsScene{};

	m_font = GetFontDefault();

	m_creditsTitle.setFontSize(Constants::g_FontSize64 * 2.0f, m_font);
	m_creditsTitle.setColor(DARKBROWN);
	m_creditsTitle.setText("CREDITS", m_font);
	
	m_credits = { { "Game done by", m_font }, { "Hypah and D2_Lx0wse", m_font }, { "With RayLib", m_font }, { "Random library from learncpp.com", m_font } };

	m_goBackText.setText("Go back to main menu", m_font);


	m_creditsTitle.setPosition(Vector2{ (m_sceneWidth - m_creditsTitle.textSize().x) / 2.0f, (m_sceneHeight / 100.0f) * 5.0f });

	constexpr float creditsFontSize{ Constants::g_FontSize64 / 1.5f };
	float verticalSpaceBetweenCredits{ creditsFontSize / 6.0f };
	for (auto& credit : m_credits) {
		credit.setFontSize(creditsFontSize, m_font);
		credit.setColor(DARKGRAY);
		credit.setPosition(
			Vector2{ (Constants::g_ScreenWidth - credit.textSize().x) / 2.0f, (Constants::g_ScreenHeight - credit.textSize().y) / 2.0f + verticalSpaceBetweenCredits }
		);

		verticalSpaceBetweenCredits += credit.fontSize();
	}

	m_goBackText.setPosition(Vector2{ (m_sceneWidth / 100.0f) * 2.0f, m_sceneHeight - m_goBackText.textSize().y});
}

void CreditsScene::exit() {
	m_font = Font{};
}