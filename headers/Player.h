#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Settings.h"
#include "StaticVars.h"
#include "TextureHandler.h"
#include "Flags.h"
#include "World.h"
#include "Log.h"
#include "HelpingFunctions.h" // toString()

class Player
{
private :
	sf::Sprite sprite{ TextureHandler::getTexture(TextureID::Alex_still_sheet) }; // TODO :: Make one sheet for one skin that will contain all poses
	//std::array<sf::Texture, 9> playerSpriteTextures; // Possbily some skins will have more or less in future but for now we set it on 9 = {1 shooting to left, 1 shooting to right, 2 run left, 2 run right, 1 jump asc, 1 jump desc, 1 still}
	sf::Vector2u hitBox = sprite.getTexture().getSize();
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f lastPlayerPos = getPosition(); // Init
	sf::Vector2f currPlayerPos = getPosition();
	float baseScale = Settings::baseScale;
	float speed = Settings::speed;
	float jumpStr = Settings::jumpStr;
	float healthPoints = Settings::healthPoints;
	float timeAlive = 0.f;

	void move(const float& deltaTime);
	void breathe(const float& deltaTime);
	void updateFlags();
public :
	Player() {
		sprite.setTextureRect(sf::IntRect{ sf::Vector2i{49, 550}, sf::Vector2i{449, 473} });
		sprite.setScale(sf::Vector2f{ baseScale, baseScale });
		sprite.setPosition(sf::Vector2f{ 200.f, 200.f });
	}

	void update(const float& deltaTime);
	void draw(sf::RenderWindow& window) const;
	sf::Vector2f getPosition() const;
};
