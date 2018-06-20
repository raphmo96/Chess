#include "Coordinates.h"
#include "Pawn.h"



Pawn::Pawn(bool a_isWhite, SDL_Surface* a_Image) :Piece(a_isWhite, a_Image) {
	//Y , X
	m_PossibleMove.push_back({ 0, a_isWhite ? 100 : -100 });
}

bool Pawn::CanMove(Coordinates a_Start, Coordinates a_End) {
	if (m_NbMove == 0 && a_Start + m_PossibleMove[0] * 2 == a_End) {
		m_NbMove++;
		return true;
	}
	return Piece::CanMove(a_Start, a_End);
}

Pawn::~Pawn()
{
}
