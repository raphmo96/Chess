#include "Coordinates.h"
#include "Bishop.h"
#include <iostream>


Bishop::Bishop(bool a_isWhite, SDL_Surface* a_Window, Coordinates a_Coord) :Piece(a_isWhite, a_Window, a_Coord)
{
	m_PossibleMove.push_back({ 100, 100 });
	m_PossibleMove.push_back({ 100, -100 });
	m_PossibleMove.push_back({ -100, 100 });
	m_PossibleMove.push_back({ -100, -100 });
	m_MaxMovement = 8;
	m_CanStackMovement = true;
	m_Type = Enums::PieceType::Bishop;
	std::cout << m_Type << std::endl;
	m_Stats = { 200, 0, 10, 0 };
	m_SkillName = "Maniac!";
	m_SkillDescription = "More pain, more gain!";
	InitStats(m_Stats);
}

Bishop::~Bishop()
{
	Piece::~Piece();
}

bool Bishop::ReceiveDamage(int a_Damage) {
	m_Damage += a_Damage;
	return Piece::ReceiveDamage(a_Damage);
}
