#ifndef ITEMS_H
#define ITEMS_H

#include <SFML/Graphics.hpp>

class Item {
	protected:
		sf::Vector2f velocity;
		float position_x;
        float position_y;

	public:
		virtual void set_random_position() = 0;
		virtual float get_y_position() = 0;
		virtual void move(const float& delta) = 0;
		virtual void draw(sf::RenderWindow& win) = 0;
		virtual sf::FloatRect get_global_bounds() = 0;
		
};

#endif //ITEMS_H