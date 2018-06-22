#include "Coordinates.h"
#include "King.h"



King::King(bool a_isWhite, SDL_Surface* a_Window) :Piece(a_isWhite, a_Window)
{
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, -100 });
	m_PossibleMove.push_back({ 100, 100 });
	m_PossibleMove.push_back({ -100, 100 });
	m_PossibleMove.push_back({ 100, -100 });
	m_PossibleMove.push_back({ -100, -100 });
	m_Name = "King";
}


King::~King()
{
	Piece::~Piece();
}
