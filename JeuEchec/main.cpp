/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "WindowRenderer.h"
#include <iostream>

int main(int argc, char* args[])
{
	WindowRenderer renderer{};
	//Start up SDL and create window
	if (!renderer.init())
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

				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					if (e.type == SDL_MOUSEMOTION) {
						int x = 0;
						int y = 0;
						SDL_GetMouseState(&x, &y);
						std::cout << x << y << std::endl;
					}
				}
			}

			//Apply the PNG image
			renderer.BlitSurface();

			//Update the surface
			renderer.UpdateWindow();
		}
	}
	system("pause");
	//Free resources and close SDL
	renderer.close();

	return 0;
}