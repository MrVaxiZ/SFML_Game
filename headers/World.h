#pragma once

#include <SFML/System/Vector2.hpp>
#include "Log.h"

class World
{
private :
	inline static const float groundPos = 350.f; // Not sure how I approach this yet so declared here for a while 

	void setBackground();
	void setBorders();
	void physics();
public :
	static const float& getGround();
};

