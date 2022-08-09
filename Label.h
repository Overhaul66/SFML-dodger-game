#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>

class Label {
	private:
		sf::RectangleShape background; //background for label
		sf::Text text; 
		sf::Font font;
		
	public:
	
		Label(const std::string& word,const bool& bg, const sf::Color& bg_color );
		void draw(sf::RenderWindow& win);
		void update_text(const std::string& new_text);
	
};

#endif //LABEL_H