#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	bool m_IsHolding;
};

