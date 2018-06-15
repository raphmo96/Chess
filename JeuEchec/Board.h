#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class BoardCase;

class Board
{
public:
	Board();
	~Board();

	//Screen dimension constants
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 800;
	const int BOARD_WIDTH = 800;
	const int BOARD_HEIGHT = 800;
	const int GRID_COLUMNS = 8;
	const int GRID_ROWS = 8;
	const int CELLSIZE = BOARD_HEIGHT / GRID_ROWS;
	const std::string IMAGE_PATH = "Images\\";

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	void UpdateWindow() { SDL_UpdateWindowSurface(m_Window); };
	//IMAGE       RECT   WINDOW           RECT
	void BlitSurface() { SDL_BlitSurface(m_BoardImage, NULL, m_ScreenSurface, NULL); }


	void DrawBoard();
private:
	std::vector<std::vector<BoardCase*>> m_BoardCases;

	//The window we'll be rendering to
	SDL_Window* m_Window = NULL;

	//The surface contained by the window
	SDL_Surface* m_ScreenSurface = NULL;

	//Current displayed PNG image
	SDL_Surface* m_BoardImage = NULL;

	//Loads individual image
	SDL_Surface* loadSurface(std::string path);

	BoardCase* GetCaseAtPos(int, int);

	bool InitCases();

	void InitChestPieces();
};

