#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <SDL_ttf.h>
#include <vector>
#include "Enums.h"

class Coordinates;
class BoardCase;
class Board;
class Piece;

class Game
{
public:
	//Return Game Instance;
	static Game* Instance();
	~Game();
	//main loop function;
	void Run();

	//Reset current game;
	void ResetGame();

	//Load game from previous save;
	void LoadGame();

	//Return the board of the game;
	Board* GetBoard() { return m_Board; }

private:
	Game();
	Game(const Game&);
	static Game* m_Instance;

	bool m_IsHolding;

	bool m_IsWhiteTurn = true;

	bool m_SkipTurn = false;

	bool m_SpellMode = false;

	Coordinates m_TempPos;

	Coordinates m_MousePos;

	BoardCase* m_CurrentCase;

	Piece* m_PreviewPiece;

	Piece* m_CurrentPiece;

	Board* m_Board;

	Enums::Spells m_SelectedSpell;

	//Save the current board state to a txt file;
	void SaveGame();

	//Button related actions;
	void GameAction(Enums::ButtonType);

	//Init turn switch
	void NextTurn(bool);

	//Active spell targeting
	void TargetSpell(bool, Enums::Spells);

	//Timer related variables;
	int m_PlayerOneTime = 0;
	int m_PlayerTwoTime = 0;
	int m_TimeSinceLastcheck = 0;

	int m_PlayerOneMana = 1;
	int m_PlayerTwoMana = 0;

	//Validate and place a piece from one case to another;
	void DropPiece(Coordinates a_Start, Coordinates a_End, bool, bool);

	void ResetPiece(BoardCase*);

	void UseSpell(BoardCase*);

	std::vector<std::tuple<Coordinates, Coordinates> > m_Moves = std::vector<std::tuple<Coordinates, Coordinates> >();

	bool m_GameIsOnGoing = false;
};

