#pragma once

#include <string>
#include <string_view>

#include "raylib.h"

#include "Constants.hpp"

class BrackeysText {
public:
	// Constructors
	BrackeysText();
	// Calls setText()
	BrackeysText(std::string_view text, const Font& font);

	// Render using given font
	void render(const Font& font) const;

	// Getters
	std::string_view text() const;
	const Vector2& textSize() const;

	const Vector2& textPosition() const;

	float fontSize() const;
	float spacing() const;
	Color color() const;

	// Setters
	// Uses font to gauge the size of the font (also based on font size and spacing)
	void setText(std::string_view text, const Font& font);
	void setPosition(const Vector2& textPosition);

	// Spacing is one tenth of the font size
	void setFontSize(float fontSize, const Font& font);
	void setColor(const Color& color);

private:
	std::string m_text{};
	Vector2 m_textSize{};

	Vector2 m_textPosition{};

	float m_fontSize{ Constants::g_FontSize64 };
	float m_spacing{ m_fontSize / 10.0f };
	Color m_color{ BLACK };
};