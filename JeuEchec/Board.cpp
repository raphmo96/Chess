#include "Coordinates.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Tower.h"
#include "BoardCase.h"
#include "Board.h"
#include "Button.h"

Board::Board()
{
	//m_TimerRectP1 = new SDL_Rect({ BOARD_WIDTH, BOARD_HEIGHT / 2 + 25, 100, 20 });
	//m_TimerRectP2 = new SDL_Rect({ BOARD_WIDTH, BOARD_HEIGHT / 2 - 25, 100, 20 });
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
				//m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
				LoadMedia();
				InitCases();
				InitChestPieces();
				InitButtons();

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
	for (int i = 0; i < GRID_ROWS; i++) {
		m_BoardCases.push_back(std::vector<BoardCase*>());
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i].push_back(new BoardCase(new SDL_Rect({ CELLSIZE*i, CELLSIZE*j, CELLSIZE, CELLSIZE }), m_Highlight));
		}
	}
	return false;
}

void Board::InitButtons() {

	m_Buttons = std::vector<Button*>();
	//Create new button and add it to buttons list
	m_Buttons.push_back(new Button(LoadSurface(IMAGE_PATH + "newButton.png"), new SDL_Rect({ BOARD_WIDTH + 150,BOARD_HEIGHT / 2 - 23,150,45 })));
	m_Buttons.push_back(new Button(LoadSurface(IMAGE_PATH + "loadButton.png"), new SDL_Rect({ BOARD_WIDTH + 310,BOARD_HEIGHT / 2 - 23,150,45 })));
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
	//Open the font
	//m_Font = TTF_OpenFont("Fonts\\hemi head bd it.ttf", 28);
	//if (m_Font == NULL)
	//{
	//	printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	//	success = false;
	//}
	m_Highlight = LoadSurface(IMAGE_PATH + "Highlight.png");
	m_Checkmatelight = LoadSurface(IMAGE_PATH + "Checkmate.png");
	return success;
}

SDL_Surface* Board::LoadSurface(std::string path)
{
	return IMG_Load(path.c_str());
}

void Board::SetTimer(int a_Player, int a_Time) {
	int seconds = (int)(a_Time / 1000) % 60;
	int minutes = (int)((a_Time / (1000 * 60)) % 60);
	int hours = (int)((a_Time / (1000 * 60 * 60)) % 24);
	SDL_Color color = { 250,250,250 };
	std::string timer = std::to_string(hours) + ": " + std::to_string(minutes) + ": " + std::to_string(seconds);
	if (a_Player) {
		//m_TimerP1 = SDL_CreateTextureFromSurface(m_Renderer, TTF_RenderText_Solid(m_Font, timer.c_str(), color));
	}
	else {
		//m_TimerP2 = SDL_CreateTextureFromSurface(m_Renderer, TTF_RenderText_Solid(m_Font, timer.c_str(), color));
	}
}

void Board::DrawUI() {
	//SDL_RenderCopy(m_Renderer, m_TimerP1, m_TimerRectP1, m_TimerRectP1);
	//SDL_RenderCopy(m_Renderer, m_TimerP2, m_TimerRectP2, m_TimerRectP2);
	for (int i = 0; i < m_Buttons.size(); i++) {
		m_Buttons[i]->Draw(m_ScreenSurface);
	}
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

bool Board::MarkPossibleMovement(BoardCase* a_Case) {
	bool flag = false;
	//Scan through the grid to show possible movement
	Piece* tempPiece;
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			//Check where piece can go
			if (a_Case->GetPiece()->CanMove(a_Case->GetCoord(), m_BoardCases[i][j]->GetCoord())) {
				//If king is moving, assert next position is safe
				if (a_Case->GetPiece()->GetName() == "King") {
					m_Kings[a_Case->GetPiece()->IsWhite()] = m_BoardCases[i][j];
				}
				//Check if King will be in danger
				tempPiece = m_BoardCases[i][j]->GetPiece();
				m_BoardCases[i][j]->SetPiece(a_Case->GetPiece());
				a_Case->SetPiece(NULL);
				if (IsKingSafe(m_BoardCases[i][j]->GetPiece()->IsWhite())) {
					m_BoardCases[i][j]->SetIsMarkedUp(true);
					flag = true;
				}

				//Set piece back to normal
				a_Case->SetPiece(m_BoardCases[i][j]->GetPiece());
				m_BoardCases[i][j]->SetPiece(tempPiece);
				if (a_Case->GetPiece()->GetName() == "King") {
					m_Kings[a_Case->GetPiece()->IsWhite()] = a_Case;
				}
			}
		}
	}
	return flag;
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

bool Board::IsCheckmate(bool a_IsWhite) {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			if (m_BoardCases[i][j]->GetPiece() == nullptr)continue;
			if (m_BoardCases[i][j]->GetPiece()->IsWhite() == a_IsWhite) {
				if (MarkPossibleMovement(m_BoardCases[i][j])) {
					ResetPossibleMovement();
					return false;
				}
			};
		}

	}
	ResetPossibleMovement();
	m_Kings[a_IsWhite]->ChangeHighlight(m_Checkmatelight);
	m_Kings[a_IsWhite]->SetIsMarkedUp(true);
	DrawBoard();
	UpdateWindow();
	return true;
}

void Board::ChangeKingCase(bool a_IsWhite, Coordinates a_Coord) {
	m_Kings[(int)a_IsWhite] = GetCaseAtPos(a_Coord);
}

void Board::ResetBoard(bool a_Continue) {

	for (int i = 0; i < m_Buttons.size(); i++) {
		delete m_Buttons[i];
	}
	m_Buttons.clear();
	for (int i = 0; i < m_BoardCases.size(); i++) {
		for (int j = 0; j < m_BoardCases.size(); j++) {
			delete m_BoardCases[i][j];
		}
		m_BoardCases[i].clear();
	}
	m_BoardCases.clear();

	if (a_Continue) {
		InitCases();
		InitChestPieces();
		InitButtons();
	}
}

void Board::Close()
{
	//Free loaded image
	SDL_FreeSurface(m_BoardImage);
	m_BoardImage = NULL;

	SDL_FreeSurface(m_Highlight);
	m_Highlight = NULL;
	SDL_FreeSurface(m_Checkmatelight);
	m_Checkmatelight = NULL;

	//Destroy Renderer
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;

	//Destroy Textures
	SDL_DestroyTexture(m_TimerP1);
	m_TimerP1 = NULL;
	SDL_DestroyTexture(m_TimerP2);
	m_TimerP2 = NULL;
	//Close font 
	//TTF_CloseFont(m_Font);
	//m_Font = NULL;

	ResetBoard(false);

	//Quit SDL subsystems
	IMG_Quit();
	//TTF_Quit();
	SDL_Quit();
}

Board::~Board() {
	delete m_TimerRectP1;
	delete m_TimerRectP2;
	Close();
}