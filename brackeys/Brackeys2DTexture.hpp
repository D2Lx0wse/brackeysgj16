#pragma once

#include <string_view>

#include "raylib.h"

#include "Constants.hpp"

class Brackeys2DTexture {
public:
	// Constructors
	Brackeys2DTexture();

	// Destructor
	~Brackeys2DTexture();

	// Loads texture, copy assigns it to m_texture
	bool loadFromFile(std::string_view filepath);

	// Frees the texture and sets m_texture back to its default values
	void exit();

	// Renders the texture to (X,Y) coordinates. 
	//  - Optionally can choose the width/height seen on screen
	//  - Optionally can choose the degrees of rotation (counter-clockwise).
	// Returns true/false based on if texture is loaded or not
	bool render(float x, float y, Vector2 scalingSize = Vector2{ 0.0f, 0.0f }, float rotation = 0.0f);

	// Getters
	Texture2D texture() const;
	bool isLoaded() const;
	
	// Multiplied by Constants::g_scalingSize
	float width() const;
	float height() const;

private:
	Texture2D m_texture{};
};