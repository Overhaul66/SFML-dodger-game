#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Game.h"


int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
    Game game;
    game.Run();
    return 0;
}
