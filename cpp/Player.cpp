#include "Player.h"

/// PRIVATE

void Player::move(const float& deltaTime)
{
	// Reset horizontal velocity every frame
	velocity.x = 0.f;

	// Handle horizontal input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		velocity.x = -speed;
		fSet(Flag::PlayerMoves, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		velocity.x = speed;
		fSet(Flag::PlayerMoves, true);
	}

	// Handle jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
		fGet(Flag::PlayerOnGround))
	{
		velocity.y = -jumpStr;
		fSet(Flag::PlayerMoves, true);
		fSet(Flag::PlayerOnGround, false);
	}

	// Apply gravity if not grounded
	if (!fGet(Flag::PlayerOnGround)) {
		velocity.y += sv::gravity.y * deltaTime;
	}

	// Apply velocity
	sprite.move(velocity * deltaTime);

	// Ground check
	if (sprite.getPosition().y >= World::getGround()) {
		sf::Vector2f pos = sprite.getPosition();
		pos.y = World::getGround(); // Snap to ground
		sprite.setPosition(pos);

		velocity.y = 0.f;
		fSet(Flag::PlayerOnGround, true);
	}
}

void Player::breathe(const float& deltaTime)
{
	// Imitate breathing only when player does not move
	if (!fGet(Flag::PlayerMoves) && fGet(Flag::PlayerOnGround)) {
		float scaleOscillation = sin(timeAlive * 1.f) * 0.005f;
		sprite.setScale(sf::Vector2f{
			baseScale + scaleOscillation,
			baseScale + scaleOscillation
			});
	}
}

void Player::updateFlags()
{
	sf::Vector2f current = getPosition();
	if (current == lastPlayerPos) {
		fSet(Flag::PlayerMoves, false);
	}
}

/// PUBLIC

void Player::update(const float& deltaTime) {
	timeAlive += deltaTime;

	move(deltaTime);
	breathe(deltaTime);
	updateFlags();

	lastPlayerPos = currPlayerPos;
	currPlayerPos = sprite.getPosition();
}

void Player::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
	return currPlayerPos;
}
