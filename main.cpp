#include <iostream>
#include <SDL.h>

#include "game.h"

int main(int argc, char* argv[]) {
	Game* game = new Game();
	game->start();
	return 0;
}