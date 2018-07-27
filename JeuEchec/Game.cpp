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

Game::~Game()
{
	delete m_Board;
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
					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);
					//Board

					if (m_MousePos.m_Y < 800 && m_MousePos.m_X < 800) {
						m_CurrentCase = m_Board->GetCaseAtPos(m_MousePos);
						if (m_SpellMode) {
							if (m_CurrentCase->GetIsTarget()) {
								UseSpell(m_CurrentCase);
							}
							else {
								m_SpellMode = false;
								m_SelectedSpell = Enums::Spells::Null;
								m_Board->ResetPossibleMovement();
							}
						}
						else {
							m_CurrentPiece = m_CurrentCase->GetPiece();
							//If a piece is clicked and is good color
							if (m_CurrentPiece != NULL) {
								if (m_IsWhiteTurn == m_CurrentCase->GetPiece()->IsWhite()) {
									m_IsHolding = true;
									//Mark possible position
									m_Board->MarkPossibleMovement(m_CurrentCase);
									m_TempPos.m_X = m_CurrentCase->m_Rect->x;
									m_TempPos.m_Y = m_CurrentCase->m_Rect->y;
								}
							}
						}
					}//UI
					else {
						GameAction(m_Board->ClickButton(m_MousePos));
					}
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					if (m_IsHolding) {
						m_IsHolding = false;

						DropPiece(m_TempPos, m_MousePos, true, m_SkipTurn);
						//ResetPossible move;
						m_Board->ResetPossibleMovement();
					}
				}
				if (m_IsHolding && e.type == SDL_MOUSEMOTION) {
					//Make the piece follow the mouse;
					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);
					m_CurrentCase->m_Rect->x = m_MousePos.m_X - m_Board->CELLSIZE / 2;
					m_CurrentCase->m_Rect->y = m_MousePos.m_Y - m_Board->CELLSIZE / 2;
				}
				if (e.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&m_MousePos.m_X, &m_MousePos.m_Y);
					if (m_MousePos.m_Y < 800 && m_MousePos.m_X < 800) {
						m_PreviewPiece = m_Board->GetCaseAtPos(m_MousePos)->GetPiece();
					}
				}
			}
			//Timer related code;
			if (m_GameIsOnGoing) {
				if (m_TimeSinceLastcheck == 0)m_TimeSinceLastcheck = SDL_GetTicks();
				if (m_IsWhiteTurn) {
					m_PlayerOneTime += SDL_GetTicks() - m_TimeSinceLastcheck;

					m_Board->SetTimer(0, m_PlayerOneTime);

				}
				else {
					m_PlayerTwoTime += SDL_GetTicks() - m_TimeSinceLastcheck;
					m_Board->SetTimer(1, m_PlayerTwoTime);

				}
				m_TimeSinceLastcheck = SDL_GetTicks();
			}


			//Check is game is done

			//Draw boards and pieces;
			m_Board->SetMana(m_PlayerOneMana, m_PlayerTwoMana);
			m_Board->BlitSurface();
			m_Board->DrawBoard();
			m_Board->DrawUI();
			if (m_CurrentCase != nullptr) {
				m_CurrentCase->DrawPiece(m_Board->GetBoardSurface());
				m_Board->DrawStat(m_CurrentCase->GetPiece());
			}
			if (m_PreviewPiece != nullptr) {
				m_Board->DrawStat(m_PreviewPiece);
			}

			m_Board->UpdateWindow();
		}
		//Free resources and close SDL;
		SaveGame();
		m_Board->Close();
	}
}

void Game::DropPiece(Coordinates a_Start, Coordinates a_End, bool a_NextTurn, bool a_SkipTurn) {
	//m_CurrentCase = m_Board->GetCaseAtPos(a_Start);
	m_CurrentCase->m_Rect->x = a_Start.m_X;
	m_CurrentCase->m_Rect->y = a_Start.m_Y;
	BoardCase* NewCase = m_Board->GetCaseAtPos(a_End);
	//Assert movement is valid;
	if (m_CurrentCase->GetPiece()->CanMove(m_TempPos, NewCase->GetCoord())) {
		//Register movement;
		m_Moves.push_back(std::make_tuple(m_CurrentCase->GetCoord() / 100, NewCase->GetCoord() / 100));
		//Keep tracks of both kinds;
		if (m_CurrentCase->GetPiece()->GetType() == Enums::PieceType::King) {
			m_Board->ChangeKingCase(m_CurrentCase->GetPiece()->IsWhite(), NewCase->GetCoord());
		}
		//Check if a piece is on the case;
		m_CurrentCase->GetPiece()->RaiseNbMove();
		if (NewCase->GetPiece() != nullptr) {
			if (NewCase->GetPiece()->ReceiveDamage(m_CurrentCase->GetPiece()->GetDamage())) {
				delete NewCase->GetPiece();
				m_PreviewPiece = nullptr;
				NewCase->SetPiece(m_CurrentCase->GetPiece());
				m_CurrentCase->SetPiece(nullptr);
			}
		}
		else {
			NewCase->SetPiece(m_CurrentCase->GetPiece());
			m_CurrentCase->SetPiece(nullptr);
		}
		if (a_NextTurn) {
			NextTurn(a_SkipTurn);
		}
	}
	m_CurrentCase = nullptr;
}

void Game::ResetPiece(BoardCase* a_Case) {
	BoardCase* NewCase = m_Board->GetCaseAtPos(a_Case->GetPiece()->GetInitialPos());
	delete NewCase->GetPiece();
	a_Case->GetPiece()->ResetStat();
	NewCase->SetPiece(a_Case->GetPiece());
	a_Case->SetPiece(nullptr);
}

void Game::GameAction(Enums::ButtonType a_Type) {
	switch (a_Type) {
	case Enums::ButtonType::Empty:
		break;
	case Enums::ButtonType::ResetGame:
		ResetGame();
		break;
	case Enums::ButtonType::LoadGame:
		LoadGame();
		break;
	case Enums::ButtonType::HealButton:
		if ((m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana) >= 1)
			TargetSpell(false, Enums::Spells::Heal);
		break;
	case Enums::ButtonType::FreezeButton:
		if ((m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana) >= 2)
			TargetSpell(true, Enums::Spells::Freeze);
		break;
	case Enums::ButtonType::RegenManaButton:
		if ((m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana) >= 3)
			TargetSpell(false, Enums::Spells::RegenMana);
		break;
	case Enums::ButtonType::SkipButton:
		if ((m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana) >= 4)
			m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana -= 4;
		m_SkipTurn = true;
		break;
	case Enums::ButtonType::RewindButton:
		if ((m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana) >= 5)
			TargetSpell(true, Enums::Spells::RegenMana);
		break;
	}
}

void Game::TargetSpell(bool a_TargetEnemy, Enums::Spells a_Spell) {
	m_Board->ResetPossibleMovement();
	m_SelectedSpell = a_Spell;
	m_SpellMode = true;
	m_Board->MarkPossibleTarget(m_IsWhiteTurn, a_TargetEnemy);
}

void Game::UseSpell(BoardCase* a_Case) {
	m_SpellMode = false;
	int cost = 0;
	switch (m_SelectedSpell) {
	case Enums::Spells::Heal:
		a_Case->GetPiece()->RegenHP(20);
		cost = 1;
		break;
	case Enums::Spells::Freeze:
		a_Case->GetPiece()->ToggleFreeze();
		cost = 2;
		break;
	case Enums::Spells::RegenMana:
		a_Case->GetPiece()->RegenMana(30);
		cost = 3;
		break;
	case Enums::Spells::Rewind:
		cost = 5;
		ResetPiece(a_Case);
		break;
	}
	(m_IsWhiteTurn ? m_PlayerOneMana : m_PlayerTwoMana) -= cost;
	m_SelectedSpell = Enums::Spells::Null;
	m_Board->ResetPossibleMovement();
}

void Game::NextTurn(bool a_SkipTurn) {
	if (!m_IsWhiteTurn) {
		m_PlayerOneMana++;
	}
	else {
		m_PlayerTwoMana++;
	}
	m_IsWhiteTurn = !m_IsWhiteTurn;
	if (!m_GameIsOnGoing)m_GameIsOnGoing = true;
	if (a_SkipTurn) {
		NextTurn(false);
		m_SkipTurn = false;
	}
}

void Game::ResetGame() {
	m_Board->ResetBoard(true);
	m_GameIsOnGoing = false;
	m_PlayerOneTime = 0;
	m_PlayerTwoTime = 0;
	m_PlayerOneMana = 1;
	m_PlayerTwoMana = 0;
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
			move += std::to_string(std::get<0>(m_Moves[i]).m_X / 100);
			move += std::to_string(std::get<0>(m_Moves[i]).m_Y / 100);
			move += std::to_string(std::get<1>(m_Moves[i]).m_X / 100);
			move += std::to_string(std::get<1>(m_Moves[i]).m_Y / 100);
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
	Coordinates start;
	Coordinates end;
	std::fstream saveFile;
	std::string move = "";
	const char* c;
	saveFile.open(fileName, std::fstream::in | std::fstream::app);
	while (std::getline(saveFile, move)) {
		c = move.c_str();
		start = { c[0] - '0',c[1] - '0' };
		end = { c[2] - '0', c[3] - '0' };
		DropPiece(start * 100, end * 100, false, false);
		//SDL_Delay(100);
	}
	saveFile.close();
}