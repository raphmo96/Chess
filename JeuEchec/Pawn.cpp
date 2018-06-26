#include "Coordinates.h"
#include "Pawn.h"
#include <math.h>
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Pawn::Pawn(bool a_isWhite, SDL_Surface* a_Image) :Piece(a_isWhite, a_Image) {
	//Y , X
	m_PossibleMove.push_back({ 0, a_isWhite ? 100 : -100 });
	m_Name = "Pawn";
}

bool Pawn::CanMove(Coordinates a_Start, Coordinates a_End) {
	//Check for Diagonal movement
	Coordinates attackMove = (a_End - (a_Start + m_PossibleMove[0]));
	Piece* attackPiece = Game::Instance()->GetBoard()->GetCaseAtPos(a_End)->GetPiece();
	if (abs(attackMove.m_X) == 100 && attackMove.m_Y == 0 && attackPiece != NULL) {
		if (attackPiece->IsWhite() != this->m_IsWhite)
			return true;
	}
	//Check for Start movement
	if (m_NbMove == 0 && a_Start + m_PossibleMove[0] * 2 == a_End &&
		Game::Instance()->GetBoard()->GetCaseAtPos(a_Start + m_PossibleMove[0] * 2)->GetPiece() == nullptr &&
		Game::Instance()->GetBoard()->GetCaseAtPos(a_Start + m_PossibleMove[0])->GetPiece() == nullptr) {
		return true;
	}
	return Piece::CanMove(a_Start, a_End);
}

Pawn::~Pawn()
{
	Piece::~Piece();
}
