#include "Coordinates.h"
#include "Queen.h"

Queen::Queen(bool a_isWhite, SDL_Surface* a_Window, Coordinates a_Coord) :Piece(a_isWhite, a_Window, a_Coord)
{
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, -100 });
	m_PossibleMove.push_back({ 100, 100 });
	m_PossibleMove.push_back({ 100, -100 });
	m_PossibleMove.push_back({ -100, 100 });
	m_PossibleMove.push_back({ -100, -100 });
	m_CanStackMovement = true;
	m_MaxMovement = 8;
	m_Type = Enums::PieceType::Queen;
	m_Stats = { 100, 50, 25, 100 };
	m_SkillName = "Recall!";
	m_SkillDescription = "Recall a piece to her side";
	InitStats(m_Stats);
}

Queen::~Queen()
{
	Piece::~Piece();
}
