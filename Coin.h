#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include "item.h"

class Coin : public Item {
	
	private:
		sf::CircleShape coin;
		
	public:
		static const int speed;
		Coin();
		void set_random_position();
		void set_random_position_y();
	    float get_y_position();
	    float get_x_position();
	    void move(const float& delta);
		void move_towards_player(const float& delta, const sf::Vector2f& player_pos);
		void draw(sf::RenderWindow& win);
		sf::FloatRect get_global_bounds();
		void set_invisible();
		bool is_invisible();
};

#endif