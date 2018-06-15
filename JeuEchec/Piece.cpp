#include "Piece.h"

Piece::Piece(bool a_isWhite, SDL_Surface* a_Image)
{
	m_IsWhite = a_isWhite;
	m_Image = a_Image;
}

void Piece::Draw(SDL_Surface* a_Window, SDL_Rect* a_Rect) {
	SDL_BlitSurface(m_Image, NULL, a_Window, a_Rect);
}

Piece::~Piece()
{
}
