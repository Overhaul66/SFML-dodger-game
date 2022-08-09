#ifndef MAGNET_H
#define MAGNET_H

#include <SFML/Graphics.hpp>
#include "Item.h"

class Magnet : public Item{
	
	private:
		sf::RectangleShape magnet;
		float speed = 100.f;
	public:
		Magnet() : magnet(sf::Vector2f(20, 20)) {
			magnet.setFillColor(sf::Color::Green);
		}
		void set_random_position() {
			 position_x = rand() % (330 - 20) ;  
			 magnet.setPosition(sf::Vector2f(position_x,position_y));
		}
		float get_y_position() {
			return magnet.getPosition().y;
		}
		void move(const float& delta) {
			velocity.y = 1 * speed * delta;
			magnet.move(0,velocity.y);
		}
		void draw(sf::RenderWindow& win) {
			win.draw(magnet);
		}
		sf::FloatRect get_global_bounds() {
			return magnet.getGlobalBounds();
		}
};

#endif //MAGNET_H