#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <future>
#include "Aliases.h"
#include "Log.h"

enum TextureID {
	// ALEX
	Alex_still_sheet,
	Alex_run_right_sheet,
	Alex_run_left_sheet,

	SIZE
};

class TextureHandler
{
private:
	static std::unordered_map<TextureID, sf::Texture> textures;
	std::future<void> preloadFuture;

	void asyncLoadAll();     // launches loading on another thread
	void loadAllTextures();  // performs actual file loading
public:
	TextureHandler() {
		// Launch async
		preloadFuture = std::async(std::launch::async, &TextureHandler::loadAllTextures, this);

		// Wait for it to finish before moving forward
		preloadFuture.wait();
	}

	// ex. TextureHandler::setTexture(TextureID::Alex_run_right, "assets/alex_right.png");
	static bool setTexture(const TextureID& texture, const string& filename);
	// ex. TextureHandler::getTexture(TextureID::Alex_run_right);
	static const sf::Texture& getTexture(const TextureID& texture);
};

