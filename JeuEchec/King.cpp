#include "Coordinates.h"
#include "King.h"



King::King(bool a_isWhite, SDL_Surface* a_Window, Coordinates a_Coord) :Piece(a_isWhite, a_Window, a_Coord)
{
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, -100 });
	m_PossibleMove.push_back({ 100, 100 });
	m_PossibleMove.push_back({ -100, 100 });
	m_PossibleMove.push_back({ 100, -100 });
	m_PossibleMove.push_back({ -100, -100 });
	m_MaxMovement = 2;
	m_Type = Enums::PieceType::King;
	m_Stats = { 250, 50, 25, 30 };
	m_SkillName = "Copulate";
	m_SkillDescription = "Can impregnate the queen to spawn now pieces";
	InitStats(m_Stats);
}


King::~King()
{
	Piece::~Piece();
}
