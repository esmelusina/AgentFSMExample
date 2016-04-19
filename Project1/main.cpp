#include "Game1.h"

int main(int argc, char **argv)
{
	//Check Game1.cpp for game code
	Game1 *pGame = new Game1(1232, 878, false, "Game1");

	pGame->RunGame();
	
	delete pGame;

	return 0;
};