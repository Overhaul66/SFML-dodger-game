#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Item.h"

class Obstacle : public Item {
	
	private:
		sf::RectangleShape rect;
		
	public:
		Obstacle();
		void set_random_position();
		void set_random_width();
	    float get_y_position();
	    void move(const float& delta);
		void draw(sf::RenderWindow& win);
		sf::FloatRect get_global_bounds();
		static float speed;
};

#endif //OBSTACLE_H