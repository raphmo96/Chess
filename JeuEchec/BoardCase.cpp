#include "Coordinates.h"
#include "Piece.h"
#include "BoardCase.h"

BoardCase::BoardCase(SDL_Rect* a_Rect, SDL_Surface* a_Highlight)
	:m_Rect(a_Rect)
	, m_Highlight(a_Highlight)
{
}

void BoardCase::DrawPiece(SDL_Surface* a_Window) {
	if (m_Piece != nullptr) {
		m_Piece->Draw(a_Window, m_Rect);
	}
}

void BoardCase::DrawHighlight(SDL_Surface* a_Window) {
	SDL_BlitSurface(m_Highlight, NULL, a_Window, m_Rect);
}

BoardCase::~BoardCase()
{
	delete m_Rect;
	if (m_Piece != nullptr) {
		delete m_Piece;
	}
}
