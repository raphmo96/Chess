#include "Coordinates.h"
#include "Pawn.h"
#include <math.h>
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"

Pawn::Pawn(bool a_isWhite, SDL_Surface* a_Window, Coordinates a_Coord) :Piece(a_isWhite, a_Window, a_Coord) {
	//Y , X
	m_PossibleMove.push_back({ 100, 0 });
	m_PossibleMove.push_back({ 0, 100 });
	m_PossibleMove.push_back({ -100, 0 });
	m_PossibleMove.push_back({ 0, -100 });
	m_PossibleMove.push_back({ 100, 100 });
	m_PossibleMove.push_back({ -100, 100 });
	m_PossibleMove.push_back({ 100, -100 });
	m_PossibleMove.push_back({ -100, -100 });
	m_CanStackMovement = false;
	m_Type = Enums::PieceType::Pawn;

	m_Stats = { 50, 10, 25, 40 };
	m_SkillName = "Formation";
	m_SkillDescription = "Moves with his direct pawn neighboor";
	InitStats(m_Stats);
}

Pawn::~Pawn()
{
	Piece::~Piece();
}
