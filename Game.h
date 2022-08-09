#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "obstacle.h"
#include "Coin.h"
#include "Player.h"
#include "Label.h"
#include "Magnet.h"
#include <vector>
#include <stdexcept>
#include "Timer.h"

class Game
{
public:
    Game();
    void Run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow mWindow;

    static const sf::Time TimePerFrame;

	std::vector<Obstacle> obstacle_holders;
	Timer obstacle_timer;
	
	std::vector<Coin> coins;
	sf::Time coin_timer = sf::Time::Zero;
	sf::Clock coin_clock;
	
	int cnt = 0; //to count the number of obstacles dodged
	size_t coins_collected = 0;
	
	Player player;
	Label coin_counter;
	
	sf::Time magnet_timer = sf::Time::Zero;
	sf::Clock magnet_clock;
	
	sf::Time magnet_gained_timer = sf::Time::Zero;
	sf::Clock magnet_gained_timer_clock;
	bool start_magnet_gained_timer;
	
	std::vector<Magnet> magnets;
	float random_magnet_timer = 10.f;

};

#endif //GAME_H