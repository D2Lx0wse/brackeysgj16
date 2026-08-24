#include "BrackeysText.hpp"

BrackeysText::BrackeysText()
	: m_text{}
	, m_textSize{}
	, m_textPosition{}
	, m_fontSize{Constants::g_FontSize64}
	, m_spacing{}
	, m_color{ BLACK }
{
	m_spacing = m_fontSize / 10.0f;
}

BrackeysText::BrackeysText(std::string_view text, const Font& font)
	: m_text{}
	, m_textSize{}
	, m_textPosition{}
	, m_fontSize{ Constants::g_FontSize64 }
	, m_spacing{}
	, m_color{ BLACK }
{
	m_spacing = m_fontSize / 10.0f;
	setText(text, font);
}


void BrackeysText::render(const Font& font) const {
	DrawTextEx(font, text().data(), textPosition(), fontSize(), spacing(), color());
}


void BrackeysText::setText(std::string_view text, const Font& font) {
	m_text = text;

	m_textSize = MeasureTextEx(font, BrackeysText::text().data(), fontSize(), spacing());
}

void BrackeysText::setPosition(const Vector2& textPosition) {
	m_textPosition = textPosition;
}

void BrackeysText::setFontSize(float fontSize) {
	m_fontSize = fontSize;
	m_spacing = m_fontSize / 10.0f;
}

void BrackeysText::setColor(const Color& color) {
	m_color = color;
}


std::string_view BrackeysText::text() const {
	return m_text;
}

const Vector2& BrackeysText::textSize() const {
	return m_textSize;
}

const Vector2& BrackeysText::textPosition() const {
	return m_textPosition;
}

float BrackeysText::fontSize() const {
	return m_fontSize;
}

float BrackeysText::spacing() const {
	return m_spacing;
}

Color BrackeysText::color() const {
	return m_color;
}