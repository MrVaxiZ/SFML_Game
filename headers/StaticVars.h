#pragma once

#include <SFML/System/Vector2.hpp>

struct StaticVars {
	inline static sf::Vector2f gravity = { 0.f, 980.f }; // pixels per second squared (like 9.8 m/s^2 but scaled)
	inline static float deltaTime = 0.f;
};