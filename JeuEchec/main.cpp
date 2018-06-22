/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Coordinates.h"
#include "Board.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Game* game = Game::Instance();;
	game->Run();
	return 0;
}