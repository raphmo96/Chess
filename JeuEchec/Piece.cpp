#include "Coordinates.h"
#include "Piece.h"
#include "BoardCase.h"
#include "Board.h"
#include "Game.h"
Piece::Piece(bool a_isWhite, SDL_Surface* a_Image, Coordinates a_Coord)
	:m_IsWhite(a_isWhite),
	m_Image(a_Image),
	m_InitialPos(a_Coord)
{
}

Piece::~Piece()
{
	SDL_FreeSurface(m_Image);
	m_Image = NULL;
}

void Piece::Draw(SDL_Surface* a_Window, SDL_Rect* a_Rect) {
	SDL_BlitSurface(m_Image, NULL, a_Window, a_Rect);
}

bool Piece::CanMove(Coordinates a_Start, Coordinates a_End) {
	Piece* tempPiece;
	Coordinates tempCoord;
	Board* board = Game::Instance()->GetBoard();
	//For each possible direction
	for (Coordinates coord : m_PossibleMove) {
		//if it can move more than one case
		if (m_CanStackMovement) {
			for (int i = 1; i < this->m_MaxMovement; i++) {
				tempCoord = a_Start + coord * i;
				//Check effectiveness
				if ((a_End - tempCoord) > (a_End - a_Start)) break;
				//Assert is in board
				if (tempCoord.m_X < 800 && tempCoord.m_Y < 800 &&
					tempCoord.m_X >= 0 && tempCoord.m_Y >= 0) {
					tempPiece = board->GetCaseAtPos(tempCoord)->GetPiece();
				}
				else { break; }
				//Check if piece can move to case
				if (tempCoord == a_End) {
					//Check if case is occupied and by who
					if (tempPiece != NULL && tempPiece->IsWhite() == this->m_IsWhite)
						break;
					return true;
				}
				else if (tempPiece != NULL && !(this->m_Type == Enums::PieceType::Knight)) {
					break;
				}
			}
		}
		else {
			//movement for single move piece
			tempCoord = a_Start + coord;
			if (tempCoord == a_End) {
				tempPiece = board->GetCaseAtPos(tempCoord)->GetPiece();
				//Assert piece is not the same color or piece moving is a pawn
				if (tempPiece != NULL && (tempPiece->IsWhite() == this->m_IsWhite))
					return false;
				return true;
			}
		}
	}
	return false;
}

bool Piece::ReceiveDamage(int a_Damage) {
	m_Hp -= (a_Damage - m_Armor);
	return m_Hp <= 0;
}

void Piece::RegenHP(int a_Qty) {
	m_Hp += a_Qty;
}

void Piece::RegenMana(int a_Qty) {
	m_Mana += a_Qty;
}

void Piece::ToggleFreeze() {
	m_IsFrozen = !m_IsFrozen;
}

void Piece::ResetStat() {
	InitStats(m_Stats);
}

void Piece::InitStats(std::tuple<int, int, int, int> a_Stat) {
	m_Hp = std::get<0>(a_Stat);
	m_Armor = std::get<1>(a_Stat);
	m_Damage = std::get<2>(a_Stat);
	m_Mana = std::get<3>(a_Stat);
}