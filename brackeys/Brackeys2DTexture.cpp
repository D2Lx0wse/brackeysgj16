#include "Brackeys2DTexture.hpp"

#ifdef __PSP__
// Only used for PSP-specific code
#include <iostream>
#endif

Brackeys2DTexture::Brackeys2DTexture()
	: m_texture{}
{
}

Brackeys2DTexture::~Brackeys2DTexture() {
	exit();
}

bool Brackeys2DTexture::loadFromFile(std::string_view filepath) {
	exit();

	m_texture = LoadTexture(filepath.data());

	return isLoaded();
}

void Brackeys2DTexture::exit() {
	UnloadTexture(m_texture);

	m_texture = Texture2D{};
}

bool Brackeys2DTexture::render(float x, float y, Vector2 scalingSize, float rotation, Color tint) const {
	if (!isLoaded())
		return false;

#ifdef __PSP__
	// Game-breaking bug where, if you seemingly render a texture that isn't a square, then memory corruption seems to be happening, leading to black squares and the game not working
	if (width() != height()) {
		std::cout << "Error width/height\n";
		return false;
	}
#endif

	Rectangle sourceRectangle{ 0.0f, 0.0f, static_cast<float>(m_texture.width), static_cast<float>(m_texture.height) };
	Rectangle destinationRectangle{ x + width() / 2.0f, y + height() / 2.0f, static_cast<float>(width()), static_cast<float>(height())};

	if (scalingSize.x < 0.0f) {
		sourceRectangle.width *= -1.0f;
		scalingSize.x *= -1.0f;
	}
	if (scalingSize.y < 0.0f) {
		sourceRectangle.height *= -1.0f;
		scalingSize.y *= -1.0f;
	}

	// If the scaling size was chosen, go with that
	if (scalingSize.x != 0.0f)
		destinationRectangle.width = scalingSize.x;
	if (scalingSize.y != 0.0f)
		destinationRectangle.height = scalingSize.y;

	DrawTexturePro(m_texture, sourceRectangle, destinationRectangle, Vector2{ width() / 2.0f, height() / 2.0f}, rotation, tint);

	return true;
}

bool Brackeys2DTexture::render(Vector2 pos, Vector2 scalingSize, float rotation, Color tint) const {
	return render(pos.x, pos.y, scalingSize, rotation, tint);
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