#include "Player.h"

bool Player::magnet_gained = false;

Player::Player() :  player(sf::Vector2f(30, 30)), magnet_rect_region(sf::Vector2f(150, 120)) {
			player.setFillColor(sf::Color::Blue);
			magnet_rect_region.setFillColor(sf::Color(0, 0, 255, 0));
			player.setPosition(sf::Vector2f(0,300.f));
			magnet_rect_region.setPosition(sf::Vector2f(0, 300.f));
			magnet_rect_region.setOrigin(50, 40);
			speed = 190.f;
}

sf::Vector2f Player::get_player_pos() {
	return sf::Vector2f(player.getPosition().x, 300.f);
}

void Player::draw(sf::RenderWindow& win) {
	win.draw(player);
	win.draw(magnet_rect_region);
}

void Player::move(float delta) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x + player.getSize().x <= 330.f) {
		direction.x += 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0 ) {
		direction.x += -1;
	}
	
	
	velocity.x = direction.x * speed * delta;
	player.setPosition(velocity.x, 300.f);
	magnet_rect_region.setPosition(velocity.x, 300.f);
	
	velocity.x = 0;
}

sf::FloatRect Player::get_global_bounds() {
	return player.getGlobalBounds();
}

void Player::reduce_life() {
	if(life > 0) {
		life--;
	}
}
void Player::increase_life() {
	if(!(life >= 3)) {
		life++;
	}
}