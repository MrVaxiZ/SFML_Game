#pragma once

#include "Aliases.h"

namespace Settings {
	/// RSTRING

	inline constexpr rstring windowTitle = "SFML PlayGround 1.0";
	inline constexpr rstring logsFolderName = "Logs";

	/// USHORT

	inline constexpr ushort windowSizeX = 800;
	inline constexpr ushort windowSizeY = 600;
	inline constexpr ushort frameLimit = 360;

	/// FLOAT
	// PLAYER
	inline constexpr float baseScale = 0.15f;
	inline constexpr float speed = 250.f;
	inline constexpr float jumpStr = 350.f;
	inline constexpr float healthPoints = 100.f;
}