#include "Coin.h"

const int Coin::speed = 100.f;

Coin::Coin() : coin(5.f) {
	coin.setFillColor(sf::Color::Yellow);
	coin.setOutlineColor(sf::Color::Green);
	coin.setOutlineThickness(0.5f);
	position_x = 0;
	position_y = 0;
}


void Coin::draw(sf::RenderWindow& win) {
	win.draw(coin);
}

void Coin::set_random_position() {
	 position_x = rand() % (330 - 10) ;  
	 coin.setPosition(sf::Vector2f(position_x,position_y));
}

sf::FloatRect Coin::get_global_bounds() {
	return coin.getGlobalBounds();
}

void Coin::set_invisible() {
	coin.setFillColor(sf::Color(0,0,0,0));
	coin.setOutlineColor(sf::Color(0,0,0,0));
}

void Coin::set_random_position_y() {
	position_y = -((rand() % 11) * 30);  
	coin.setPosition(sf::Vector2f(position_x,position_y));
}

float Coin::get_y_position() {
	return coin.getPosition().y;
}

float Coin::get_x_position() {
	return coin.getPosition().x;
}


void Coin::move(const float& delta) {
	velocity.y = 1 * speed * delta;
	coin.move(0,velocity.y);
}

void Coin::move_towards_player(const float& delta, const sf::Vector2f& player_pos) {
	coin.move(player_pos.x * delta * 10, player_pos.y * delta * 10);
}

bool Coin::is_invisible() {
	auto alpha_channel = coin.getFillColor().a;
	if(alpha_channel == 0)
		return true;
	return false;
}