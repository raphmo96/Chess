#include "Coordinates.h"
#include "Piece.h"
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Game* Game::m_Instance = NULL;

Game* Game::Instance() {
	if (m_Instance == NULL) {
		m_Instance = new Game();
	}
	return m_Instance;
}

Game::~Game()
{

}

void Game::Run() {
	//Start up SDL and create window
	if (!m_Board.Init())
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

					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);

					m_CurrentCase = m_Board.GetCaseAtPos(m_MousePos);
					m_CurrentPiece = m_CurrentCase->GetPiece();
					//If a piece is clicked and is good color
					if (m_CurrentPiece != NULL) {
						if (m_IsWhiteTurn == m_CurrentCase->GetPiece()->IsWhite()) {
							m_IsHolding = true;
							//Mark possible position
							m_Board.MarkPossibleMovement(m_CurrentCase);
							m_TempPos.m_X = m_CurrentCase->m_Rect->x;
							m_TempPos.m_Y = m_CurrentCase->m_Rect->y;
						}
					}
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					if (m_IsHolding) {
						//ResetPossible move
						m_IsHolding = false;
						m_Board.ResetPossibleMovement();
						DropPiece();
					}
				}
				if (e.type == SDL_MOUSEMOTION && m_IsHolding) {
					//Make the piece follow the mouse
					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);
					m_CurrentCase->m_Rect->x = m_MousePos.m_X - m_Board.CELLSIZE / 2;
					m_CurrentCase->m_Rect->y = m_MousePos.m_Y - m_Board.CELLSIZE / 2;
					std::cout << m_MousePos.m_X << " | " << m_MousePos.m_Y << std::endl;
				}
			}

			//Draw boards and pieces;
			m_Board.BlitSurface();
			m_Board.DrawBoard();
			m_Board.UpdateWindow();
			if (m_CurrentCase != NULL) m_CurrentCase->DrawPiece(m_Board.GetBoardSurface());
		}
		//Free resources and close SDL;
		m_Board.Close();
	}
}

void Game::DropPiece() {
	BoardCase* NewCase = m_Board.GetCaseAtPos(m_MousePos);
	m_CurrentCase->m_Rect->x = m_TempPos.m_X;
	m_CurrentCase->m_Rect->y = m_TempPos.m_Y;
	//Assert movement is valid
	if (m_CurrentCase->GetPiece()->CanMove(m_CurrentCase->GetCoord(), NewCase->GetCoord())) {
		delete NewCase->GetPiece();
		NewCase->SetPiece(m_CurrentCase->GetPiece());
		m_CurrentCase->GetPiece()->RaiseNbMove();
		m_CurrentCase->SetPiece(NULL);
		m_IsWhiteTurn = !m_IsWhiteTurn;
	}
	else {
	}
	m_CurrentCase = NULL;
}
