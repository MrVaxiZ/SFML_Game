// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>

// System
#include <chrono>
#include <thread>

// Local
#include "Log.h"
#include "Aliases.h"
#include "Settings.h"
#include "Flags.h"
#include "StaticVars.h"
#include "HelpingFunctions.h"
#include "Player.h"

int main()
{
	// Create a window with a title and dimensions
	sf::RenderWindow window(
		sf::VideoMode(
			sf::Vector2u(
				Settings::windowSizeX,
				Settings::windowSizeY
			)
		),
		string(Settings::windowTitle)
	);

	window.setFramerateLimit(Settings::frameLimit); // Perhaps useless due to deltaTime but leave for now

	sf::Clock deltaClock; // Timer

	static TextureHandler textureHandler; // Loads all the textures

	Player player;

	while (window.isOpen())
	{
		// Calculate deltaTime at start of frame
		sv::deltaTime = deltaClock.restart().asSeconds();

		// Slow mo
		//sv::deltaTime = sv::deltaTime / 5;

		// Event handling
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
			{
				log(inf, "Pressed Key : " + toString(keyEvent->code), true);

				// Player movement is located in Player.h/.cpp
				switch (keyEvent->code) {
				case sf::Keyboard::Key::I :
					Flags::printAllFlagsStatus();
					break;
				case sf::Keyboard::Key::Escape :
					window.close();
					break;
				default:
					//log(inf, "Pressed Key : " + toString(keyEvent->code) + " is not supported!", true);
					break;
				}
			}
			else if (const auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
			{
				switch (mouseEvent->button)
				{
				case sf::Mouse::Button::Left :
					fFlip(Flag::LeftMouseBtnPressed);
					log(inf, "Event<MouseButtonPressed> LEFT", true);
					break;
				case sf::Mouse::Button::Right :
					fFlip(Flag::RightMouseBtnPressed);
					log(inf, "Event<MouseButtonPressed> RIGHT", true);
					break;
				default:
					break;
				}
			}
			else if (const auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>())
			{
				switch (mouseEvent->button)
				{
				case sf::Mouse::Button::Left:
					fFlip(Flag::LeftMouseBtnPressed);
					log(inf, "Event<MouseButtonReleased> LEFT", true);
					break;
				case sf::Mouse::Button::Right:
					fFlip(Flag::RightMouseBtnPressed);
					log(inf, "Event<MouseButtonReleased> RIGHT", true);
					break;
				default:
					break;
				}
			}
			else if (event->is<sf::Event::FocusLost>())
			{
				if (fGet(Flag::IsFocus)) {
					fSet(Flag::IsFocus, false);
					log(inf, "FOCUS IS LOST | VAL : " + toString(fGet(Flag::IsFocus)), true);
				}
			}
			else if (event->is<sf::Event::FocusGained>())
			{
				if (!fGet(Flag::IsFocus)) {
					fSet(Flag::IsFocus, true);
					log(inf, "FOCUS IS GAINED | VAL : " + toString(fGet(Flag::IsFocus)), true);
				}
			}
		}

		// UPDATES

		player.update(sv::deltaTime);

		// DRAWS

		window.clear(sf::Color::Red);
		player.draw(window);
		window.display();
	}

	return 0;
}
