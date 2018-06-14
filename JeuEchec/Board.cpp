#include "Board.h"

Board::Board()
{
	InitCases();
}


Board::~Board()
{
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
		m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	m_BoardImage = loadSurface("Images\\Board.png");
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
	SDL_Rect rect = { 0, 0, BOARD_WIDTH / GRID_COLUMNS, BOARD_HEIGHT / GRID_ROWS };
	for (int i = 0; i < GRID_ROWS; i++) {
		m_BoardCases.push_back(std::vector<BoardCase*>());
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i].push_back(new BoardCase());//Add X and Y coordinates based on indexes
		}
	}
	return false;
}

BoardCase* Board::GetCaseAtPos(int x, int y) {
	return NULL;
}

void Board::InitChestPieces() {
	Piece* newPiece = nullptr;
	BoardCase* boardCase = nullptr;
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			if (i == 0 || i == 7) {
				boardCase = GetCaseAtPos(i, j);

				switch (j) {
				case 0:
				case 7:
					//tower
					newPiece = new Tower(i > 3);
					break;
				case 1:
				case 6:
					//Knight
					newPiece = new Knight(i > 3);
					break;
				case 2:
				case 5:
					//bishop
					newPiece = new Bishop(i > 3);
					break;
				case 3:
					//Queen
					newPiece = new Queen(i > 3);
					break;
				case 4:
					//King
					newPiece = new King(i > 3);
					break;
				}
				boardCase->SetPiece(newPiece);
			}
			else if (i == 1 || i == 6) {
				boardCase = GetCaseAtPos(i, j);
				boardCase->SetPiece(new Pawn(i > 3));
			}
			if (boardCase != nullptr) {
				boardCase->DrawPiece();
				boardCase = nullptr;
			}

		}
	}
};