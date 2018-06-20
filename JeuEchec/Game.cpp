#include "Coordinates.h"
#include "Piece.h"
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Game::Game()
{
	m_Board;
}

Game::~Game()
{
}

void Game::Run() {
	//Start up SDL and create window
	if (!m_Board.init())
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

					SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);

					m_CurrentCase = m_Board.GetCaseAtMousePos(m_MousePos);
					if (m_CurrentCase->GetPiece() != NULL) {
						if (m_IsWhiteTurn == m_CurrentCase->GetPiece()->IsWhite()) {
							m_IsHolding = true;
							m_TempPos.x = m_CurrentCase->m_Rect->x;
							m_TempPos.y = m_CurrentCase->m_Rect->y;
						}
					}
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					if (m_IsHolding) {
						m_IsHolding = false;
						DropPiece();
					}

				}
				if (e.type == SDL_MOUSEMOTION && m_IsHolding) {
					SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
					m_CurrentCase->m_Rect->x = m_MousePos.x - m_Board.CELLSIZE / 2;
					m_CurrentCase->m_Rect->y = m_MousePos.y - m_Board.CELLSIZE / 2;
					std::cout << m_MousePos.x << " | " << m_MousePos.y << std::endl;
				}

				//Apply the PNG image

				//Update the surface
			}
			m_Board.BlitSurface();
			m_Board.DrawBoard();
			m_Board.UpdateWindow();
			if (m_CurrentCase != NULL) m_CurrentCase->DrawPiece(m_Board.GetBoardSurface());
		}
		//Free resources and close SDL
		m_Board.close();
	}
}

void Game::DropPiece() {
	BoardCase* NewCase = m_Board.GetCaseAtMousePos(m_MousePos);

	m_CurrentCase->m_Rect->x = m_TempPos.x;
	m_CurrentCase->m_Rect->y = m_TempPos.y;

	if (m_CurrentCase->GetPiece()->CanMove(m_CurrentCase->GetCoord(), NewCase->GetCoord())) {
		NewCase->SetPiece(m_CurrentCase->GetPiece());
		m_CurrentCase->SetPiece(NULL);
		m_IsWhiteTurn = !m_IsWhiteTurn;
	}
	else {
	}
	m_CurrentCase = NULL;
}
