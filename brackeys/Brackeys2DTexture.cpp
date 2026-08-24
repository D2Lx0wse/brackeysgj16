#include "Brackeys2DTexture.hpp"

Brackeys2DTexture::Brackeys2DTexture()
	: m_texture{}
{
}

Brackeys2DTexture::~Brackeys2DTexture() {
	exit();
}

bool Brackeys2DTexture::loadFromFile(std::string_view filepath) {
	if (isLoaded())
		exit();

	m_texture = LoadTexture(filepath.data());

	return isLoaded();
}

void Brackeys2DTexture::exit() {
	UnloadTexture(m_texture);

	m_texture = Texture2D{};
}

bool Brackeys2DTexture::render(float x, float y, Vector2 scalingSize, float rotation) {
	if (!isLoaded())
		return false;

	const Rectangle sourceRectangle{ 0.0f, 0.0f, static_cast<float>(m_texture.width), static_cast<float>(m_texture.height) };
	Rectangle destinationRectangle{ x + width() / 2.0f, y + height() / 2.0f, static_cast<float>(width()), static_cast<float>(height())};

	// If the scaling size was chosen, go with that
	if (scalingSize.x != 0.0f)
		destinationRectangle.width = scalingSize.x;
	if (scalingSize.y != 0.0f)
		destinationRectangle.height = scalingSize.y;

	DrawTexturePro(m_texture, sourceRectangle, destinationRectangle, Vector2{ width() / 2.0f, height() / 2.0f}, rotation, WHITE);

	return true;
}

Texture2D Brackeys2DTexture::texture() const {
	return m_texture;
}

bool Brackeys2DTexture::isLoaded() const {
	return IsTextureValid(m_texture);
}

float Brackeys2DTexture::width() const {
	return m_texture.width * Constants::g_ScalingSize;
}

float Brackeys2DTexture::height() const {
	return m_texture.height * Constants::g_ScalingSize;
}