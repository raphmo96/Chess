#include "Game.h"
#include "Board.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::Run() {
	Board board{};
	//Start up SDL and create window
	if (!board.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				if (e.type == SDL_MOUSEBUTTONDOWN) {
					m_IsHolding = true;
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					m_IsHolding = false;
				}
				if (e.type == SDL_MOUSEMOTION && m_IsHolding) {
					int x = 0;
					int y = 0;
					SDL_GetMouseState(&x, &y);
					std::cout << x << " | " << y << std::endl;
				}

				//Apply the PNG image

				//Update the surface
			}
			board.BlitSurface();
			board.DrawBoard();
			board.UpdateWindow();
		}
		//Free resources and close SDL
		board.close();
	}
}
