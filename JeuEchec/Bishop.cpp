#include "Coordinates.h"
#include "Bishop.h"



Bishop::Bishop(bool a_isWhite, SDL_Surface* a_Window) :Piece(a_isWhite, a_Window)
{
	m_PossibleMove.push_back({ 100, 100 });
	m_PossibleMove.push_back({ 100, -100 });
	m_PossibleMove.push_back({ -100, 100 });
	m_PossibleMove.push_back({ -100, -100 });
	m_CanStackMovement = true;
	m_Name = "Bishop";
}

Bishop::~Bishop()
{
	Piece::~Piece();
}
