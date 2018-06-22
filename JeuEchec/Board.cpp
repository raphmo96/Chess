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

bool Board::Init()
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
				LoadMedia();
				InitCases();
				InitChestPieces();

			}
		}
	}
	return success;
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
					newPiece = new Tower(j < 3, LoadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Tower.png"));
					break;
				case 1:
				case 6:
					//Knight
					newPiece = new Knight(j < 3, LoadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Knight.png"));
					break;
				case 2:
				case 5:
					//bishop
					newPiece = new Bishop(j < 3, LoadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Bishop.png"));
					break;
				case 3:
					//King
					newPiece = new King(j < 3, LoadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "King.png"));
					m_Kings[(int)j < 3] = boardCase;
					break;
				case 4:
					//Queen
					newPiece = new Queen(j < 3, LoadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Queen.png"));
					break;
				}
				boardCase->SetPiece(newPiece);
			}
			else if (j == 1 || j == 6) {
				boardCase = GetCaseAtPos(i, j);
				boardCase->SetPiece(new Pawn(j < 3, LoadSurface(IMAGE_PATH + (j > 3 ? "B" : "W") + "Pawn.png")));
			}
			if (boardCase != nullptr) {
				boardCase->DrawPiece(m_ScreenSurface);
				boardCase = nullptr;
			}
		}
	}
}

bool Board::InitCases() {
	SDL_Surface* high = LoadSurface(IMAGE_PATH + "Highlight.png");
	for (int i = 0; i < GRID_ROWS; i++) {
		m_BoardCases.push_back(std::vector<BoardCase*>());
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i].push_back(new BoardCase(new SDL_Rect({ CELLSIZE*i, CELLSIZE*j, CELLSIZE, CELLSIZE }), high));
		}
	}
	BoardCase* knigtd = m_BoardCases[1][5];
	return false;
}

bool Board::LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	m_BoardImage = LoadSurface(IMAGE_PATH + "Board.png");
	if (m_BoardImage == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	return success;
}

SDL_Surface* Board::LoadSurface(std::string path)
{
	return IMG_Load(path.c_str());
}

void Board::DrawBoard() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			if (m_BoardCases[i][j]->GetIsMarkedUp()) m_BoardCases[i][j]->DrawHighlight(m_ScreenSurface);
			m_BoardCases[i][j]->DrawPiece(m_ScreenSurface);
		}
	}
}

BoardCase* Board::GetCaseAtPos(int x, int y) {
	return m_BoardCases[x][y];
}

BoardCase* Board::GetCaseAtPos(Coordinates a_MousePos) {
	if (a_MousePos.m_X < 800 && a_MousePos.m_Y < 800 &&
		a_MousePos.m_X >= 0 && a_MousePos.m_Y >= 0) {
		return m_BoardCases[a_MousePos.m_X / 100][a_MousePos.m_Y / 100];
	}
	return NULL;
}

void Board::MarkPossibleMovement(BoardCase* a_Case) {
	//Scan through the grid to show possible movement
	Piece* tempPiece;
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			//Check where piece can go
			if (a_Case->GetPiece()->CanMove(a_Case->GetCoord(), m_BoardCases[i][j]->GetCoord())) {
				//Check if King will be in danger
				tempPiece = m_BoardCases[i][j]->GetPiece();
				m_BoardCases[i][j]->SetPiece(a_Case->GetPiece());
				a_Case->SetPiece(NULL);
				if (IsKingSafe(m_BoardCases[i][j]->GetPiece()->IsWhite())) {
					m_BoardCases[i][j]->SetIsMarkedUp(true);
				}
				//Set piece back to normal
				a_Case->SetPiece(m_BoardCases[i][j]->GetPiece());
				m_BoardCases[i][j]->SetPiece(tempPiece);
			}
		}
	}
}

void Board::ResetPossibleMovement() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i][j]->SetIsMarkedUp(false);
		}
	}
}

bool Board::IsKingSafe(bool a_IsWhite) {
	Piece* tempPiece;
	//Check for each piece
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			tempPiece = m_BoardCases[i][j]->GetPiece();
			//If piece != IsWhite
			if (tempPiece != nullptr) {
				if (tempPiece->IsWhite() != a_IsWhite) {
					//check if can move on King's case
					if (tempPiece->CanMove(m_BoardCases[i][j]->GetCoord(), m_Kings[(int)a_IsWhite]->GetCoord()))
						return false;
				}
			}

		}
	}
	return true;
}

void Board::IsCheckmate(bool a_IsWhite) {

}

void Board::ChangeKingCase(bool a_IsWhite, Coordinates a_Coord) {
	m_Kings[(int)a_IsWhite] = GetCaseAtPos(a_Coord);
}

void Board::Close()
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

Board::~Board() {
	Close();
}