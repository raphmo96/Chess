#include "Coordinates.h"
#include "Knight.h"
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Knight::Knight(bool a_isWhite, SDL_Surface* a_Window, Coordinates a_Coord) :Piece(a_isWhite, a_Window, a_Coord)
{
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ 0, -100 });

	m_CanStackMovement = true;
	m_MaxMovement = 5;
	m_Type = Enums::PieceType::Knight;

	m_Stats = { 50, 50, 75, 25 };
	m_SkillName = "Charge!";
	m_SkillDescription = "Charge will hurt everyone in its path";
	InitStats(m_Stats);
}

bool Knight::CanMove(Coordinates a_Start, Coordinates a_End) {
	return Piece::CanMove(a_Start, a_End);
}

Knight::~Knight()
{
	Piece::~Piece();
}
