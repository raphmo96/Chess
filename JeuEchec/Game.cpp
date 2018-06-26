#include "Coordinates.h"
#include "Piece.h"
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Game* Game::m_Instance = NULL;

Game::Game() {
	m_Board = new Board();
}

Game* Game::Instance() {
	if (m_Instance == NULL) {
		m_Instance = new Game();
	}
	return m_Instance;
}

void Game::Run() {
	//Start up SDL and create window
	if (!m_Board->Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;
		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				if (e.type == SDL_MOUSEBUTTONDOWN) {
					if (!m_GameIsOnGoing && !m_Board->IsCheckmate(m_IsWhiteTurn)) {
						m_GameIsOnGoing = true;
					}
					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);
					//Board
					if (m_MousePos.m_Y < 800 && m_MousePos.m_X < 800) {
						m_CurrentCase = m_Board->GetCaseAtPos(m_MousePos);
						m_CurrentPiece = m_CurrentCase->GetPiece();
						//If a piece is clicked and is good color
						if (m_CurrentPiece != NULL && m_GameIsOnGoing) {
							if (m_IsWhiteTurn == m_CurrentCase->GetPiece()->IsWhite()) {
								m_IsHolding = true;
								//Mark possible position
								m_Board->MarkPossibleMovement(m_CurrentCase);
								m_TempPos.m_X = m_CurrentCase->m_Rect->x;
								m_TempPos.m_Y = m_CurrentCase->m_Rect->y;
							}
						}
					}//UI
					else {
						if (m_MousePos.m_X > BOARD_WIDTH + 150 && m_MousePos.m_Y > BOARD_HEIGHT / 2 - 23
							&& m_MousePos.m_X < BOARD_WIDTH + 300 && m_MousePos.m_Y < BOARD_HEIGHT / 2 + 45) {
							ResetGame();
							continue;
						}
						else if (m_MousePos.m_X > BOARD_WIDTH + 310 && m_MousePos.m_Y > BOARD_HEIGHT / 2 - 23
							&& m_MousePos.m_X < BOARD_WIDTH + 460 && m_MousePos.m_Y < BOARD_HEIGHT / 2 + 45) {
							LoadGame();
							continue;
						}
					}
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					if (m_IsHolding) {
						//ResetPossible move
						m_IsHolding = false;
						DropPiece();
						m_Board->ResetPossibleMovement();
						m_GameIsOnGoing = !m_Board->IsCheckmate(m_IsWhiteTurn);
					}
				}
				if (e.type == SDL_MOUSEMOTION && m_IsHolding) {
					//Make the piece follow the mouse
					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);
					m_CurrentCase->m_Rect->x = m_MousePos.m_X - m_Board->CELLSIZE / 2;
					m_CurrentCase->m_Rect->y = m_MousePos.m_Y - m_Board->CELLSIZE / 2;
					std::cout << m_MousePos.m_X << " | " << m_MousePos.m_Y << std::endl;
				}
			}
			//Timer related code
		//	if (m_TimeSinceLastcheck == 0)m_TimeSinceLastcheck = SDL_GetTicks();
		//	if (m_IsWhiteTurn) {
		//		m_PlayerOneTime += m_TimeSinceLastcheck - SDL_GetTicks();
		//		if (m_PlayerTwoTime % 1000 == 0) {
		//			m_Board->SetTimer(0, m_PlayerOneTime);
		//		}
		//	}
		//	else {
		//		m_PlayerTwoTime += m_TimeSinceLastcheck - SDL_GetTicks();;
		//		if (m_PlayerTwoTime % 1000 == 0) {
		//			m_Board->SetTimer(1, m_PlayerTwoTime);
		//		}
		//	}
		//	m_TimeSinceLastcheck = SDL_GetTicks();

			//Check is game is done

			//Draw boards and pieces;
			m_Board->BlitSurface();
			m_Board->DrawBoard();
			m_Board->DrawUI();
			if (m_CurrentCase != NULL) m_CurrentCase->DrawPiece(m_Board->GetBoardSurface());
			m_Board->UpdateWindow();
			//m_Board->Render();
		}
		//Free resources and close SDL;
		SaveGame();
		m_Board->Close();
	}
}

void Game::DropPiece() {
	BoardCase* NewCase = m_Board->GetCaseAtPos(m_MousePos);
	m_CurrentCase->m_Rect->x = m_TempPos.m_X;
	m_CurrentCase->m_Rect->y = m_TempPos.m_Y;
	//Assert movement is valid
	if (NewCase->GetIsMarkedUp()) {
		m_Moves.push_back(std::make_tuple(m_CurrentCase->GetCoord() / 100, NewCase->GetCoord() / 100));
		if (m_CurrentCase->GetPiece()->GetName() == "King") {
			m_Board->ChangeKingCase(m_CurrentCase->GetPiece()->IsWhite(), NewCase->GetCoord());
		}
		//TODO Move piece to side of board
		delete NewCase->GetPiece();
		NewCase->SetPiece(m_CurrentCase->GetPiece());
		m_CurrentCase->GetPiece()->RaiseNbMove();
		m_CurrentCase->SetPiece(NULL);
		m_IsWhiteTurn = !m_IsWhiteTurn;
	}
	m_CurrentCase = NULL;
}

void Game::DropPiece(Coordinates a_Start, Coordinates a_End) {
	m_CurrentCase = m_Board->GetCaseAtPos(a_Start * 100);
	BoardCase* NewCase = m_Board->GetCaseAtPos(a_End * 100);
	//Assert movement is valid
	if (m_CurrentCase->GetPiece()->CanMove(m_CurrentCase->GetCoord(), NewCase->GetCoord())) {
		m_Moves.push_back(std::make_tuple(m_CurrentCase->GetCoord() / 100, NewCase->GetCoord() / 100));
		//TODO Move piece to side of board
		delete NewCase->GetPiece();
		NewCase->SetPiece(m_CurrentCase->GetPiece());
		m_CurrentCase->GetPiece()->RaiseNbMove();
		m_CurrentCase->SetPiece(NULL);
		m_IsWhiteTurn = !m_IsWhiteTurn;
	}
	m_CurrentCase = NULL;
}

void Game::ResetGame() {
	m_Board->ResetBoard(true);
	m_IsWhiteTurn = true;
	m_Moves.clear();
}

void Game::SaveGame() {
	char fileName[] = "save.txt";
	std::fstream saveFile;
	std::string move = "";
	if (m_Moves.size() > 0) {
		saveFile.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
		for (int i = 0; i < m_Moves.size(); i++) {
			move += std::to_string(std::get<0>(m_Moves[i]).m_X);
			move += std::to_string(std::get<0>(m_Moves[i]).m_Y);
			move += std::to_string(std::get<1>(m_Moves[i]).m_X);
			move += std::to_string(std::get<1>(m_Moves[i]).m_Y);
			move += "\n";
			saveFile << move;
			move = "";
		}
		saveFile.close();
	}
}

void Game::LoadGame() {
	m_Moves.clear();
	char fileName[] = "save.txt";
	std::fstream saveFile;
	std::string move = "";
	const char* c;
	saveFile.open(fileName, std::fstream::in | std::fstream::app);
	while (std::getline(saveFile, move)) {
		c = move.c_str();
		DropPiece({ c[0] - '0',c[1] - '0' }, { c[2] - '0',c[3] - '0' });
		//SDL_Delay(100);
	}
	saveFile.close();
}

Game::~Game()
{
	delete m_Board;
}
