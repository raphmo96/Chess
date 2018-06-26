#include "Coordinates.h"
#include "Knight.h"
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Knight::Knight(bool a_isWhite, SDL_Surface* a_Window) :Piece(a_isWhite, a_Window)
{
	m_PossibleMove.push_back({ 100, 200 });
	m_PossibleMove.push_back({ 200, 100 });
	m_PossibleMove.push_back({ -100, 200 });
	m_PossibleMove.push_back({ -200, 100 });
	m_PossibleMove.push_back({ 100, -200 });
	m_PossibleMove.push_back({ 200, -100 });
	m_PossibleMove.push_back({ -100, -200 });
	m_PossibleMove.push_back({ -200, -100 });
	m_Name = "Knight";
}

bool Knight::CanMove(Coordinates a_Start, Coordinates a_End) {
	for (Coordinates coord : m_PossibleMove) {
		if (a_Start + coord == a_End) {
			Piece* piece = Game::Instance()->GetBoard()->GetCaseAtPos(a_Start + coord)->GetPiece();
			if (piece != NULL && piece->IsWhite() == this->m_IsWhite)
				return false;
			return true;
		}
	}
	return false;
}

Knight::~Knight()
{
	Piece::~Piece();
}
