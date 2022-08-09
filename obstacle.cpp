#include "obstacle.h"

float Obstacle::speed = 100.f; 

Obstacle::Obstacle() : rect(sf::Vector2f(50, 10)) {
	rect.setFillColor(sf::Color::Red);
}

void Obstacle::draw(sf::RenderWindow& win) {
	win.draw(rect);
}

void Obstacle::set_random_position() {
	 float ran_x_pos = (rand() % 11) * 20;  
	 rect.setPosition(sf::Vector2f(ran_x_pos, 0));
}

void Obstacle::set_random_width() {
	float ran_width = ((rand() % 11) + 3) * 10;
	rect.setSize(sf::Vector2f(ran_width, 10));
}

sf::FloatRect Obstacle::get_global_bounds() {
	return rect.getGlobalBounds();
}

float Obstacle::get_y_position() {
	return rect.getPosition().y;
}

void Obstacle::move(const float& delta) {
	velocity.y = 1 * speed * delta;
	rect.move(0,velocity.y);
}
