#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
#include "Enums.h"

class BoardCase;
class Piece;
class Coordinates;
class Button;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int BOARD_WIDTH = 800;
const int BOARD_HEIGHT = 800;
const int GRID_COLUMNS = 8;
const int GRID_ROWS = 8;
const std::string IMAGE_PATH = "Images\\";

class Board
{
public:
	Board();
	~Board();

	//Game constants
	const int CELLSIZE = BOARD_HEIGHT / GRID_ROWS;

	//Frees media and shuts down SDL
	void Close();

	//Update the window surface
	void UpdateWindow() { SDL_UpdateWindowSurface(m_Window); };

	//IMAGE       RECT   WINDOW           RECT
	//Apply image to a certain surface
	void BlitSurface() { SDL_BlitSurface(m_BoardImage, NULL, m_ScreenSurface, NULL); }

	//Render UI

	//DrawBoard
	void DrawBoard();

	//DrawUI
	void DrawUI();

	//Clear the highlight
	void ResetPossibleMovement();

	//Keep track of kings movements
	void ChangeKingCase(bool, Coordinates);

	//Print time of player
	void SetTimer(int, int);

	//Add a piece to the side of the board
	//void AddPieceToStack();

	//Reset Board
	void ResetBoard(bool);

	//Add a button to be drawn
	void AddButton(SDL_Surface*, SDL_Rect*, Enums::ButtonType);

	//Given a piece, draw its stat in its color's rect
	void DrawStat(Piece*);

	//Starts up SDL and creates window
	bool Init();

	//Loads media
	bool LoadMedia();

	//Highlight the possible movement of the piece held
	void MarkPossibleMovement(BoardCase*);

	void SetMana(int a_P1, int a_P2) { m_ManaP1 = a_P1; m_ManaP2 = a_P2; }

	void MarkPossibleTarget(bool,bool);

	//King is lost
	bool IsCheckmate(bool);

	Enums::ButtonType ClickButton(Coordinates);

	//Return the boardCase at a certain position give a coordinates
	BoardCase* GetCaseAtPos(Coordinates);

	//Return the boardCase at a certain position give two indexes
	BoardCase* GetCaseAtPos(int, int);

	//Get main surface
	SDL_Surface* GetBoardSurface() { return m_ScreenSurface; }


private:
	std::vector<std::vector<BoardCase*>> m_BoardCases;

	//The window we'll be rendering to
	SDL_Window* m_Window = NULL;

	//The renderer
	SDL_Renderer* m_Renderer;

	//The surface contained by the window
	SDL_Surface* m_ScreenSurface = NULL;

	//Current displayed PNG image
	SDL_Surface* m_BoardImage = NULL;

	SDL_Surface* m_Highlight = NULL;
	SDL_Surface* m_Checkmatelight = NULL;

	SDL_Surface* m_Spellmark = NULL;

	//Loads individual image
	SDL_Surface* LoadSurface(std::string path);

	BoardCase* m_Kings[2];

	Piece* m_PickedUpPiece;


	//Globaly used font
	TTF_Font* m_Font;
	SDL_Color m_Color;

	//Timer rects
	SDL_Rect* m_TimerRectP1;
	SDL_Rect* m_TimerRectP2;

	//Text to texture
	SDL_Surface* m_TimerP1;
	SDL_Surface* m_TimerP2;

	SDL_Rect* m_StatsP1;
	SDL_Rect* m_StatsP2;

	SDL_Rect* m_RectManaP1;
	SDL_Rect* m_RectManaP2;

	int m_ManaP1 = 0;
	int m_ManaP2 = 0;

	SDL_Surface* m_StatsSurface;

	//Button Array
	std::vector<Button*> m_Buttons;

	//Initialize button array;
	void InitButtons();

	//Initialize board;
	bool InitCases();

	//Initialize pieces;
	void InitChestPieces();

	//Return the name of the type;
	std::string GetTypeName(Enums::PieceType);

};

