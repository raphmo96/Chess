#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Coordinates;
class Piece;

class BoardCase
{
public:
	BoardCase(SDL_Rect*);
	~BoardCase();

	Piece* GetPiece() { return m_Piece; };
	void SetPiece(Piece* a_Piece) { m_Piece = a_Piece; };

	SDL_Rect* m_Rect;
	Coordinates GetCoord() { return { m_Rect->x,m_Rect->y }; };

	void DrawPiece(SDL_Surface*);

private:
	Piece * m_Piece;

};

