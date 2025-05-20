#pragma once

#include <bitset>
#include "Log.h"
#include "HelpingFunctions.h"

enum class Flag : size_t {
	IsFocus,
	LeftMouseBtnPressed,
	RightMouseBtnPressed,
	PlayerMoves,
	PlayerOnGround,

	SIZE // Always keep this last
};

class Flags {
private:
	inline static std::bitset<static_cast<size_t>(Flag::SIZE)> flags;

public:
	static void set(const Flag& flag, const bool& value) {
		flags.set(static_cast<size_t>(flag), value);
	}

	static void clear(const Flag& flag) {
		flags.reset(static_cast<size_t>(flag));
	}

	static bool get(const Flag& flag) {
		return flags.test(static_cast<size_t>(flag));
	}

	static void flip(const Flag& flag) {
		flags.flip(static_cast<size_t>(flag));
	}

	static void printAllFlagsStatus() {
		log(inf, "========= [Flags Status] ========", true);
		for (size_t i = 0; i < static_cast<size_t>(Flag::SIZE); ++i) {
			const auto flag = static_cast<Flag>(i);
			string flagName;

			switch (flag) {
			case Flag::IsFocus:              flagName = "IsFocus";				break;
			case Flag::LeftMouseBtnPressed:  flagName = "LeftMouseBtnPressed";	break;
			case Flag::RightMouseBtnPressed: flagName = "RightMouseBtnPressed"; break;
			case Flag::PlayerMoves:          flagName = "PlayerMoves";			break;
			case Flag::PlayerOnGround:       flagName = "PlayerOnGround";		break;
			default:                         flagName = "Unknown";				break;
			}

			log(inf, "FLAG : " + flagName + " | VALUE : " + toString(get(flag)), true);
		}
		log(inf, "==================================", true);
	}
};
