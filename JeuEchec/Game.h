#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Coordinates;
class BoardCase;
class Board;
class Piece;

class Game
{
public:
	static Game* Instance();
	~Game();
	//main loop function
	void Run();

	//Return the board of the game
	Board& GetBoard() { return m_Board; };
private:
	Game() {};
	Game(const Game&);
	//Get Game instance
	static Game* m_Instance;

	bool m_IsHolding;
	bool m_IsWhiteTurn = true;

	Coordinates m_TempPos;

	Coordinates m_MousePos;

	BoardCase* m_CurrentCase;

	Piece* m_CurrentPiece;

	Board m_Board;

	//Validate and place a piece from one case to another
	void DropPiece();
};

