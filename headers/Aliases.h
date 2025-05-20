#pragma once

#include <iostream>
#include <string_view>
#include "StaticVars.h"

// Defines

#define Sleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define ILog(x) std::cout << "INF : " << x << std::endl // Information Console Log
#define WLog(x) std::cout << "WAR : " << x << std::endl // Warning Console Log
#define ELog(x) std::cerr << "ERR : " << x << std::endl // Error Console Log
#define FLog(x) std::cerr << "FAT : " << x << std::endl // Fatal Console Log
#define fSet(x,y)	Flags::set(x,y)	// Flags Set Flag
#define fGet(x)		Flags::get(x)	// Flags Get Flag
#define fFlip(x)	Flags::flip(x)	// Flags Flip Flag
#define fClear(x)	Flags::clear(x)	// Flags Clear Flag
#define sv StaticVars // StaticVars

// Usings

using ushort = unsigned short;
using string = std::string;
using rstring = std::string_view; // rstring = read-only string
using cstring = char*;