#include "Bullet.h"

void Bullets::addBullet(const sf::Vector2f& pos) {
    vecBullets.emplace_back(pos.x, pos.y);
}

void Bullets::removeDistantBullets() {
    vecBullets.erase(
        std::remove_if(vecBullets.begin(), vecBullets.end(),
            [](const Bullet& b) {
                return b.pos.x > Settings::windowSizeX || b.pos.y > Settings::windowSizeY;
            }),
        vecBullets.end()
    );
}