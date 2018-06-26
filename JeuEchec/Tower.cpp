#include "Coordinates.h"
#include "Tower.h"

Tower::Tower(bool a_isWhite, SDL_Surface* a_Window) :Piece(a_isWhite, a_Window)
{
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, -100 });
	m_CanStackMovement = true;
	m_Name = "Tower";
}

Tower::~Tower()
{
	Piece::~Piece();
}
