#pragma once

#include <vector>
#include <algorithm>
#include "Log.h"
#include "Settings.h"

struct Bullet {
    sf::Vector2f pos; 

    Bullet(float x, float y){
        pos.x = x;
        pos.y = y;
    };
};

class Bullets {
private:
std::vector<Bullet> vecBullets;

public:
void addBullet(const sf::Vector2f& pos);
void removeDistantBullets();
};