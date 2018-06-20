#include "Coordinates.h"
#include "Knight.h"



Knight::Knight(bool a_isWhite, SDL_Surface* a_Window) :Piece(a_isWhite, a_Window)
{
	m_PossibleMove.push_back({ 100, 200 });
	m_PossibleMove.push_back({ 200, 100 });
	m_PossibleMove.push_back({ -100, 200 });
	m_PossibleMove.push_back({ -200, 100 });
}

bool Knight::CanMove(Coordinates a_Start, Coordinates a_End) {
	return Piece::CanMove(a_Start, a_End);
}

Knight::~Knight()
{
}
