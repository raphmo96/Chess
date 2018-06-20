#include "Coordinates.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Tower.h"
#include "BoardCase.h"
#include "Board.h"
#include <math.h>

Board::Board()
{
}

Board::~Board()
{
	SDL_FreeSurface(m_ScreenSurface);
	SDL_FreeSurface(m_BoardImage);
	close();
}

bool Board::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		m_Window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				m_ScreenSurface = SDL_GetWindowSurface(m_Window);
				loadMedia();
				InitCases();
				InitChestPieces();

			}
		}
	}

	return success;
}

bool Board::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	m_BoardImage = loadSurface(IMAGE_PATH + "Board.png");
	if (m_BoardImage == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	return success;
}

void Board::close()
{
	//Free loaded image
	SDL_FreeSurface(m_BoardImage);
	m_BoardImage = NULL;

	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* Board::loadSurface(std::string path)
{
	return IMG_Load(path.c_str());
}

bool Board::InitCases() {
	for (int i = 0; i < GRID_ROWS; i++) {
		m_BoardCases.push_back(std::vector<BoardCase*>());
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i].push_back(new BoardCase(new SDL_Rect({ CELLSIZE*i, CELLSIZE*j, CELLSIZE, CELLSIZE })));
		}
	}
	BoardCase* knigtd = m_BoardCases[1][5];
	return false;
}

void Board::DrawBoard() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i][j]->DrawPiece(m_ScreenSurface);
		}
	}
}

BoardCase* Board::GetCaseAtPos(int x, int y) {
	return m_BoardCases[x][y];
}

BoardCase* Board::GetCaseAtMousePos(Coordinates a_MousePos) {
	if (a_MousePos.x <= 800) {
		return GetCaseAtPos(a_MousePos.x / 100, a_MousePos.y / 100);
	}
	return NULL;
}

void Board::InitChestPieces() {
	Piece* newPiece = nullptr;
	BoardCase* boardCase = nullptr;
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			if (j == 0 || j == 7) {
				boardCase = GetCaseAtPos(i, j);

				switch (i) {
				case 0:
				case 7:
					//tower
					newPiece = new Tower(j < 3, loadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Tower.png"));
					break;
				case 1:
				case 6:
					//Knight
					newPiece = new Knight(j < 3, loadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Knight.png"));
					break;
				case 2:
				case 5:
					//bishop
					newPiece = new Bishop(j < 3, loadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Bishop.png"));
					break;
				case 3:
					//Queen
					newPiece = new Queen(j < 3, loadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Queen.png"));
					break;
				case 4:
					//King
					newPiece = new King(j < 3, loadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "King.png"));
					break;
				}
				boardCase->SetPiece(newPiece);
			}
			else if (j == 1 || j == 6) {
				boardCase = GetCaseAtPos(i, j);
				boardCase->SetPiece(new Pawn(j < 3, loadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Pawn.png")));
			}
			if (boardCase != nullptr) {
				boardCase->DrawPiece(m_ScreenSurface);
				boardCase = nullptr;
			}
		}
	}
};