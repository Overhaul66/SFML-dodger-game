#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
	private:
		float x_pos;
		sf::Vector2f direction;
		sf::Vector2f velocity;
		float speed;
		sf::RectangleShape player;
		sf::RectangleShape magnet_rect_region;
		size_t life;
	
	public:
	static bool magnet_gained;
		
	
	public:
		Player();
		void draw(sf::RenderWindow& win);
		void move(float delta);
		sf::FloatRect get_global_bounds();
		void reduce_life();
		void increase_life();
		sf::Vector2f get_player_pos();
		sf::FloatRect get_global_bounds_of_magnet_region() {
			return magnet_rect_region.getGlobalBounds();
		}
		size_t get_life() {
			return life;
		}
};

#endif //PLAYER_H