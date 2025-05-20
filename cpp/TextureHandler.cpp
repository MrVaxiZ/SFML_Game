#include "TextureHandler.h"

/// PRIVATE

std::unordered_map<TextureID, sf::Texture> TextureHandler::textures;

// Async launch
void TextureHandler::asyncLoadAll() {
	preloadFuture = std::async(std::launch::async, &TextureHandler::loadAllTextures, this);
}

// Actual loader (private)
void TextureHandler::loadAllTextures() {
	setTexture(TextureID::Alex_still_sheet, "assets/Alex_sheet_still.png");
	setTexture(TextureID::Alex_run_right_sheet, "assets/Alex_sheet_right_direction.png");
	setTexture(TextureID::Alex_run_left_sheet, "assets/Alex_sheet_left_direction.png");
}

/// PUBLIC

bool TextureHandler::setTexture(const TextureID& texture, const string& filename)
{
	sf::Texture tex;
	if (!tex.loadFromFile(filename))
		return false;

	textures[texture] = std::move(tex);
	return true;
}

const sf::Texture& TextureHandler::getTexture(const TextureID& texture)
{
	auto it = textures.find(texture);
	if (it != textures.end()) {
		return it->second;
	}
	else {
		throw std::runtime_error("Failed to get texture: texture not found in map.");
	}
}
