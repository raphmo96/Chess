#include "Coordinates.h"
#include "Game.h"
#include "Board.h"
#include "BoardCase.h"
#include "Button.h"
#include "Enums.h"
#include "PieceFactory.h"

Board::Board()
{
	m_TimerRectP1 = new SDL_Rect({ BOARD_WIDTH + 25, BOARD_HEIGHT / 2 - 60, 100, 20 });
	m_TimerRectP2 = new SDL_Rect({ BOARD_WIDTH + 25, BOARD_HEIGHT / 2 + 30, 100, 20 });
	m_StatsP1 = new SDL_Rect({ BOARD_WIDTH + 25,BOARD_HEIGHT - 240,50,20 });
	m_StatsP2 = new SDL_Rect({ BOARD_WIDTH + 25,10,50,20 });
	m_RectManaP1 = new SDL_Rect({ BOARD_WIDTH + 25, BOARD_HEIGHT / 2 + 50, 100, 20 });
	m_RectManaP2 = new SDL_Rect({ BOARD_WIDTH + 25, BOARD_HEIGHT / 2 - 80, 100, 20 });
	//m_StatsRect;
}

Board::~Board() {
	delete m_TimerRectP1;
	delete m_TimerRectP2;
	delete m_StatsP1;
	delete m_StatsP2;
	Close();
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
				TTF_Init();
				LoadMedia();
				InitCases();
				InitChestPieces();
				InitButtons();

				SetTimer(0, 0);
				SetTimer(1, 0);
				DrawUI();
			}
		}
	}
	return success;
}

void Board::InitChestPieces() {
	Piece* newPiece = nullptr;
	BoardCase* boardCase = nullptr;
	Coordinates coord;
	bool isWhite = false;
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			if (j == 0 || j == 7) {
				boardCase = GetCaseAtPos(i, j);
				coord = boardCase->GetCoord();
				isWhite = j > 3;
				switch (i) {
				case 0:
				case 7:
					//Tower
					newPiece = PieceFactory::CreatePiece(Enums::PieceType::Tower, isWhite, IMAGE_PATH, coord);
					break;
				case 1:
				case 6:
					//Knight
					newPiece = PieceFactory::CreatePiece(Enums::PieceType::Knight, isWhite, IMAGE_PATH, coord);
					break;
				case 2:
				case 5:
					//Bishop
					newPiece = PieceFactory::CreatePiece(Enums::PieceType::Bishop, isWhite, IMAGE_PATH, coord);
					break;
				case 3:
					//King
					newPiece = PieceFactory::CreatePiece(Enums::PieceType::King, isWhite, IMAGE_PATH, coord);
					m_Kings[(int)isWhite] = boardCase;
					break;
				case 4:
					//Queen
					newPiece = PieceFactory::CreatePiece(Enums::PieceType::Queen, isWhite, IMAGE_PATH, coord);
					break;
				}
				boardCase->SetPiece(newPiece);
			}
			else if (j == 1 || j == 6) {
				isWhite = j > 3;
				boardCase = GetCaseAtPos(i, j);
				boardCase->SetPiece(PieceFactory::CreatePiece(Enums::PieceType::Pawn, isWhite, IMAGE_PATH, coord));

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
			m_BoardCases[i].push_back(new BoardCase(new SDL_Rect({ CELLSIZE*i, CELLSIZE*j, CELLSIZE, CELLSIZE }), m_Highlight, m_Spellmark));
		}
	}
	return false;
}

void Board::InitButtons() {

	m_Buttons = std::vector<Button*>();
	AddButton(LoadSurface(IMAGE_PATH + "newButton.png"), new SDL_Rect({ BOARD_WIDTH + 325,BOARD_HEIGHT / 2 + 20,150,45 }), Enums::ButtonType::ResetGame);
	AddButton(LoadSurface(IMAGE_PATH + "loadButton.png"), new SDL_Rect({ BOARD_WIDTH + 325,BOARD_HEIGHT / 2 - 40,150,45 }), Enums::ButtonType::LoadGame);
	AddButton(TTF_RenderText_Solid(m_Font, "Heal", m_Color), new SDL_Rect({ BOARD_WIDTH + 150,BOARD_HEIGHT / 2 - 70,150,45 }), Enums::ButtonType::HealButton);
	AddButton(TTF_RenderText_Solid(m_Font, "Freeze", m_Color), new SDL_Rect({ BOARD_WIDTH + 150,BOARD_HEIGHT / 2 - 40,150,45 }), Enums::ButtonType::FreezeButton);
	AddButton(TTF_RenderText_Solid(m_Font, "Regen Mana", m_Color), new SDL_Rect({ BOARD_WIDTH + 150,BOARD_HEIGHT / 2 - 10,150,45 }), Enums::ButtonType::RegenManaButton);
	AddButton(TTF_RenderText_Solid(m_Font, "Skip", m_Color), new SDL_Rect({ BOARD_WIDTH + 150,BOARD_HEIGHT / 2 + 20,150,45 }), Enums::ButtonType::SkipButton);
	AddButton(TTF_RenderText_Solid(m_Font, "Rewind", m_Color), new SDL_Rect({ BOARD_WIDTH + 150,BOARD_HEIGHT / 2 + 50,150,45 }), Enums::ButtonType::RewindButton);
}

void Board::AddButton(SDL_Surface* a_Image, SDL_Rect* a_Rect, Enums::ButtonType a_Type) {
	m_Buttons.push_back(new Button(a_Image, a_Rect, a_Type));
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
	m_Font = TTF_OpenFont("Fonts\\hemi head bd it.ttf", 22);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	m_Color = { 255,255,255 };
	m_Highlight = LoadSurface(IMAGE_PATH + "Highlight.png");
	m_Checkmatelight = LoadSurface(IMAGE_PATH + "Checkmate.png");
	m_Spellmark = LoadSurface(IMAGE_PATH + "Spellmark.png");
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
	std::string timer = std::to_string(hours) + ": " + std::to_string(minutes) + ": " + std::to_string(seconds);
	//SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, timer.c_str(), m_Color);
	if (a_Player) {
		SDL_FreeSurface(m_TimerP1);
		m_TimerP1 = TTF_RenderText_Solid(m_Font, timer.c_str(), m_Color);
	}
	else {
		SDL_FreeSurface(m_TimerP2);
		m_TimerP2 = TTF_RenderText_Solid(m_Font, timer.c_str(), m_Color);
	}
}

void Board::DrawUI() {
	for (int i = 0; i < m_Buttons.size(); i++) {
		m_Buttons[i]->Draw(m_ScreenSurface);
	}
	SDL_Surface* surface;
	SDL_BlitSurface(m_TimerP1, NULL, m_ScreenSurface, m_TimerRectP1);
	SDL_BlitSurface(m_TimerP2, NULL, m_ScreenSurface, m_TimerRectP2);
	surface = TTF_RenderText_Solid(m_Font, std::to_string(m_ManaP1).c_str(), m_Color);
	SDL_BlitSurface(TTF_RenderText_Solid(m_Font, ("Mana: " + std::to_string(m_ManaP1)).c_str(), m_Color), NULL, m_ScreenSurface, m_RectManaP1);
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(m_Font, std::to_string(m_ManaP2).c_str(), m_Color);
	SDL_BlitSurface(TTF_RenderText_Solid(m_Font, ("Mana: " + std::to_string(m_ManaP2)).c_str(), m_Color), NULL, m_ScreenSurface, m_RectManaP2);
	SDL_FreeSurface(surface);
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

Enums::ButtonType Board::ClickButton(Coordinates a_Pos)
{
	for (int i = 0; i < m_Buttons.size(); i++) {
		if (m_Buttons[i]->Contains(a_Pos)) {
			return m_Buttons[i]->GetType();
		}
	}
	return Enums::ButtonType::Empty;
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
				m_BoardCases[i][j]->SetIsMarkedUp(true);
			}
		}
	}
}

void Board::MarkPossibleTarget(bool a_WhiteTurn, bool a_EnemyTarget) {
	//Scan through the grid to show possible target
	Piece* tempPiece;
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			//Check for target
			if (m_BoardCases[i][j]->GetPiece() == nullptr) continue;
			if (a_EnemyTarget) {
				if (m_BoardCases[i][j]->GetPiece()->IsWhite() != a_WhiteTurn) {
					m_BoardCases[i][j]->SetIsMarkedUp(true);
					m_BoardCases[i][j]->SetIsTarget(true);
				}
			}
			else {
				if (m_BoardCases[i][j]->GetPiece()->IsWhite() == a_WhiteTurn) {
					m_BoardCases[i][j]->SetIsMarkedUp(true);
					m_BoardCases[i][j]->SetIsTarget(true);
				}
			}
		}
	}
}


void Board::ResetPossibleMovement() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			m_BoardCases[i][j]->SetIsMarkedUp(false);
			m_BoardCases[i][j]->SetIsTarget(false);
		}
	}
}

bool Board::IsCheckmate(bool a_IsWhite) {
	if (m_Kings[a_IsWhite]->GetPiece()->GetHP() < 0) {
		m_Kings[a_IsWhite]->ChangeHighlight(m_Checkmatelight);
		m_Kings[a_IsWhite]->SetIsMarkedUp(true);
		DrawBoard();
		UpdateWindow();
		return true;
	}
	return false;
}

void Board::ChangeKingCase(bool a_IsWhite, Coordinates a_Coord) {
	m_Kings[(int)a_IsWhite] = GetCaseAtPos(a_Coord);
}

std::string Board::GetTypeName(Enums::PieceType a_Type) {
	switch (a_Type) {
	case Enums::PieceType::Pawn:
		return "Pawn";
	case Enums::PieceType::Tower:
		return "Tower";
	case Enums::PieceType::Knight:
		return "Knight";
	case Enums::PieceType::Bishop:
		return "Bishop";
	case Enums::PieceType::Queen:
		return "Queen";
	case Enums::PieceType::King:
		return "King";
	}
}
void Board::DrawStat(Piece* a_Piece) {
	SDL_Rect* pos = a_Piece->IsWhite() ? m_StatsP1 : m_StatsP2;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("Type: " + GetTypeName(a_Piece->GetType())).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y += 25;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("Damage: " + std::to_string(a_Piece->GetDamage())).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y += 25;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("HP: " + std::to_string(a_Piece->GetHP())).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y += 25;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("Armor: " + std::to_string(a_Piece->GetArmor())).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y += 25;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("Mana: " + std::to_string(a_Piece->GetMana())).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y += 25;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("Skill: " + a_Piece->GetSkillName()).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y += 25;
	m_StatsSurface = TTF_RenderText_Solid(m_Font, ("Desc: " + a_Piece->GetSkillDescription()).c_str(), m_Color);
	SDL_BlitSurface(m_StatsSurface, NULL, m_ScreenSurface, pos);
	SDL_FreeSurface(m_StatsSurface);
	pos->y -= 150;
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
		DrawUI();
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
	SDL_FreeSurface(m_Spellmark);
	m_Spellmark = NULL;

	//Destroy Renderer
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;

	//Destroy Textures
	SDL_FreeSurface(m_TimerP1);
	m_TimerP1 = NULL;
	SDL_FreeSurface(m_TimerP2);
	m_TimerP2 = NULL;

	//Close font 
	TTF_CloseFont(m_Font);
	m_Font = NULL;

	ResetBoard(false);

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
