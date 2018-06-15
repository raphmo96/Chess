#include "BoardCase.h"
#include "Piece.h"

BoardCase::BoardCase(SDL_Rect* a_Rect)
	:m_Rect(a_Rect)
{
}

void BoardCase::DrawPiece(SDL_Surface* a_Window) {
	if (m_Piece != nullptr) {
		m_Piece->Draw(a_Window, m_Rect);
	}
}

BoardCase::~BoardCase()
{
}
