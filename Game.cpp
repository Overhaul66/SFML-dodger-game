//
// Created by Giovanni Cortes on 07/05/20.
//

#include "Game.h"
#include <iostream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(330, 480), "Your Awesome Game!"), 
coin_counter("Hello", true, sf::Color::Red), coins_collected(0), 
start_magnet_gained_timer(false),
obstacle_timer(170.f/ Obstacle::speed)
{
	
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event{};

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }

    }
}

void Game::update(sf::Time deltaTime)
{
    // TODO: Update your objects here
    // Example: mWindow.draw(mPlayer);
	
	//timer
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
		player.move(deltaTime.asSeconds());
	}
	
	
	if(obstacle_timer.timer_ended()) {
		//create new obstacle
		Obstacle new_platform;
		new_platform.set_random_position();
		new_platform.set_random_width();
		obstacle_holders.push_back(new_platform);
		
		obstacle_timer.restart();
	}
	
	coin_timer += coin_clock.restart();
	
	if(coin_timer.asSeconds() >= 2.f ) {
		//create coins
		int random_num_coin = (rand() % 5) + 2;
		
		//create random number of coins
		for(int x = 0; x < random_num_coin; ++x) {
			Coin new_coin;
			new_coin.set_random_position();
			new_coin.set_random_position_y();
			coins.push_back(new_coin);
		}
		
		coin_timer = sf::Time::Zero;
		
	}
	
	
	magnet_timer += magnet_clock.restart();
	
	if(magnet_timer.asSeconds() >= random_magnet_timer ) {
		Magnet new_magnet;
		new_magnet.set_random_position();
		magnets.push_back(new_magnet);
		
		magnet_timer = sf::Time::Zero;
		random_magnet_timer = ((rand() % 3) + 1) * 30.f;
		
	}
	
	//move obstacles
	if(obstacle_holders.begin() != obstacle_holders.end()) {
		for(auto it = obstacle_holders.begin(); it != obstacle_holders.end(); ++it) {
			(*it).move(deltaTime.asSeconds());
		}
	}
	
	//move coins
		if(coins.begin() != coins.end()) {
			for(auto it = coins.begin(); it != coins.end(); ++it) {
				(*it).move(deltaTime.asSeconds());
			}
		}
	
	//if magnet is collected move coin towards player
	if(Player::magnet_gained) {
		if(coins.begin() != coins.end()) {
			for(auto it = coins.begin(); it != coins.end(); ++it) {
				if((player.get_global_bounds_of_magnet_region().intersects((*it).get_global_bounds()))) {
					sf::Vector2f pos;
					pos.x = player.get_player_pos().x - (*it).get_x_position();
					pos.y = player.get_player_pos().y - (*it).get_y_position();
					(*it).move_towards_player(deltaTime.asSeconds(), pos);
				}
			}
		}
	}
	
	//magnet power 
	if(start_magnet_gained_timer) {
		magnet_gained_timer += magnet_gained_timer_clock.restart(); 
		if(magnet_gained_timer.asSeconds() >= 15.f) {
			Player::magnet_gained = false;
			magnet_gained_timer = sf::Time::Zero;
			start_magnet_gained_timer = false;
			std::cout << "Magnet done\n";
		}
		
	}
	 
	//move magnets
	if(magnets.begin() != magnets.end()) {
		for(auto it = magnets.begin(); it != magnets.end(); ++it) {
			(*it).move(deltaTime.asSeconds());
		}
	}
	
	//delete obstacle if it moves out of screen
	if(obstacle_holders.begin() != obstacle_holders.end()) {
		auto first_platform = obstacle_holders.begin();
		if((*first_platform).get_y_position() > 480.f) {
			obstacle_holders.erase(first_platform);
			cnt++;
		}
	}
	
	//delete coin if it moves out of screen
	if(coins.begin() != coins.end()) {
		auto first_coin = coins.begin();
		if((*first_coin).get_y_position() >= 480.f) {
			coins.erase(first_coin);
		}
	}
	
	//increase obstacle speed when some certain amount is dodged by the player
	if(cnt >= 15) {
		if(!(Obstacle::speed >= 400.f))
			Obstacle::speed += 0.06;
	}
	
	
	//check player collision with coin
	if(coins.begin() != coins.end()) {
		for(auto it = coins.begin(); it != coins.end(); ++it) {
			if(player.get_global_bounds().intersects((*it).get_global_bounds())) {
				if(!(*it).is_invisible()) {
					coins_collected += 1;
					(*it).set_invisible();
				}
			}
		}
	}
	
	
	std::vector<Obstacle>::iterator current_obstacle = obstacle_holders.end();
	//check player collision with obstacle
	if(obstacle_holders.begin() != obstacle_holders.end()) {
		for(auto it = obstacle_holders.begin(); it != obstacle_holders.end(); ++it) {
			if(player.get_global_bounds().intersects((*it).get_global_bounds())) {
				//die
			}
		}
	}
	

	//check player collision with magnet
	if(magnets.begin() != magnets.end()) {
		for(auto it = magnets.begin(); it != magnets.end(); ++it) {
			if(player.get_global_bounds().intersects((*it).get_global_bounds()) && !(Player::magnet_gained)) {
				Player::magnet_gained = true;
				start_magnet_gained_timer = true;
				std::cout << "collided with magnet\n";
			}
		}
	}
	
	coin_counter.update_text("Coins : " + std::to_string(coins_collected));

}

void Game::render()
{
    mWindow.clear();

    // TODO: Draw your objects here
	if(obstacle_holders.begin() != obstacle_holders.end()) {
		for(auto it = obstacle_holders.begin(); it != obstacle_holders.end(); ++it) {
			(*it).draw(mWindow);
		}
	}
	
	if(coins.begin() != coins.end()) {
		for(auto it =coins.begin(); it != coins.end(); ++it) {
			(*it).draw(mWindow);
		}
	}
	
	if(magnets.begin() != magnets.end()) {
		for(auto it =magnets.begin(); it != magnets.end(); ++it) {
			(*it).draw(mWindow);
		}
	}
	
	player.draw(mWindow);
	coin_counter.draw(mWindow);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    // TODO: Key events for your game
    // Example:
    // if (key == sf::Keyboard::W)
    // {
    // mIsMovingUp = isPressed;
    // }
}
