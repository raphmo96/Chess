#include "Coordinates.h"
#include "Tower.h"

Tower::Tower(bool a_isWhite, SDL_Surface* a_Window, Coordinates a_Coord) :Piece(a_isWhite, a_Window, a_Coord)
{
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, -100 });
	m_CanStackMovement = true;
	m_Type = Enums::PieceType::Tower;
	m_Stats = { 75, 50, 10, 30 };
	m_SkillName = "Anchor!";
	m_SkillDescription = "Anchor itself, reducing movement and raising armor.";
	InitStats(m_Stats);
}

Tower::~Tower()
{
	Piece::~Piece();
}
