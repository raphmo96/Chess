#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Coordinates;
class BoardCase;
class Board;

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	bool m_IsHolding;
	bool m_IsWhiteTurn = true;

	Coordinates m_TempPos;
	Coordinates m_MousePos;
	BoardCase* m_CurrentCase;
	Board m_Board;

	void DropPiece();
};

