#include "Label.h"

Label::Label(const std::string& word, const bool& bg, const sf::Color& bg_color ) {
	if(bg) {
		background.setFillColor(bg_color);
	}
	font.loadFromFile("sansation.ttf");
	text.setFont(font);
	text.setString(word);
	text.setCharacterSize(20);
}

void Label::draw(sf::RenderWindow& win) {
	win.draw(text);
}

void Label::update_text(const std::string& new_text) {
	text.setString(new_text);
}