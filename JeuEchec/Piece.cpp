#include "Coordinates.h"
#include "Piece.h"
#include "Board.h"
Piece::Piece(bool a_isWhite, SDL_Surface* a_Image)
{
	m_IsWhite = a_isWhite;
	m_Image = a_Image;
}

void Piece::Draw(SDL_Surface* a_Window, SDL_Rect* a_Rect) {
	SDL_BlitSurface(m_Image, NULL, a_Window, a_Rect);
}

bool Piece::CanMove(Coordinates a_Start, Coordinates a_End) {
	for (Coordinates coord : m_PossibleMove) {
		if (m_CanStackMovement) {
			for (int i = 0; i < BOARD_HEIGHT; i++) {
				if (a_Start + coord * i == a_End) {
					m_NbMove++;
					return true;
				}
			}
		}
		else {
			if (a_Start + coord == a_End) {
				m_NbMove++;
				return true;
			}
		}
	}
	return false;
}

Piece::~Piece()
{
	SDL_FreeSurface(m_Image);
}
