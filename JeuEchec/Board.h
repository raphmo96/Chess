#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <time.h>

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

class Board
{
public:
	Board();
	~Board();

	//Game constants
	const int CELLSIZE = BOARD_HEIGHT / GRID_ROWS;
	const std::string IMAGE_PATH = "Images\\";

	//Starts up SDL and creates window
	bool Init();

	//Loads media
	bool LoadMedia();

	//Frees media and shuts down SDL
	void Close();

	void UpdateWindow() { SDL_UpdateWindowSurface(m_Window); };

	//IMAGE       RECT   WINDOW           RECT
	//Apply image to a certain surface
	void BlitSurface() { SDL_BlitSurface(m_BoardImage, NULL, m_ScreenSurface, NULL); }

	//Render UI
	void Render() { SDL_RenderPresent(m_Renderer); }

	SDL_Renderer* GetRenderer() { return m_Renderer; }

	//Return the boardCase at a certain position give a coordinates
	BoardCase* GetCaseAtPos(Coordinates);
	//Return the boardCase at a certain position give two indexes
	BoardCase* GetCaseAtPos(int, int);

	//DrawBoard
	void DrawBoard();

	//DrawUI
	void DrawUI();

	//Highlight the possible movement of the piece held
	bool MarkPossibleMovement(BoardCase*);

	//Clear the highlight
	void ResetPossibleMovement();

	//Assert King is safe
	bool IsKingSafe(bool);

	//Keep track of kings movements
	void ChangeKingCase(bool, Coordinates);

	bool IsCheckmate(bool);

	//Print time of player
	void SetTimer(int, int);

	//Add a piece to the side of the board
	void AddPieceToStack();

	//Reset Board
	void ResetBoard(bool);

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

	//Loads individual image
	SDL_Surface* LoadSurface(std::string path);

	BoardCase* m_Kings[2];

	Piece* m_PickedUpPiece;

	void InitButtons();

	//Globaly used font
	//TTF_Font* m_Font;

	//Timer rects
	SDL_Rect* m_TimerRectP1;
	SDL_Rect* m_TimerRectP2;

	//Text to texture
	SDL_Texture* m_TimerP1;
	SDL_Texture* m_TimerP2;

	//Button Array
	std::vector<Button*> m_Buttons;

	//Initialize board;
	bool InitCases();

	//Initialize pieces;
	void InitChestPieces();
};

