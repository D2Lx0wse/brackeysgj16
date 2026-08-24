#pragma once

#include <string>
#include <string_view>

#include "raylib.h"

#include "Constants.hpp"

class BrackeysText {
public:
	BrackeysText();

	void render();

	// Setters
	void setText(std::string_view text);
	void setPosition(const Vector2& textPosition);

	// Getters
	std::string_view text() const;
	Vector2 textSize() const;

	float fontSize() const;
	float spacing() const;
	Color color() const;

private:
	std::string m_text{};

	Vector2 m_textPosition{};
	Vector2 m_textSize{};

	float m_fontSize{ Constants::g_FontSize64 };
	float m_spacing{ m_fontSize / 10.0f };
	Color m_color{ BLACK };
};