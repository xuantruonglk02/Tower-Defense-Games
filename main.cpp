#include <iostream>
#include <SDL.h>

#include "game.h"

int main(int argc, char* argv[]) {
	Game* game = new Game();
	game->start();
	
	delete game;
	game = NULL;
	return 0;
}