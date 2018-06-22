#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Coordinates;
class Piece;

class BoardCase
{
public:
	BoardCase(SDL_Rect*, SDL_Surface*);
	~BoardCase();

	//Return the piece it contains or null if empty
	Piece* GetPiece() { return m_Piece; };
	//Set piece
	void SetPiece(Piece* a_Piece) { m_Piece = a_Piece; };

	SDL_Rect* m_Rect;

	//Return current coordinates of the rectangle
	Coordinates GetCoord() { return { m_Rect->x,m_Rect->y }; };

	//Assert is highlight
	bool GetIsMarkedUp() { return m_isMarkedUp; }
	//Set highlight
	void SetIsMarkedUp(bool a_IsMarked) { m_isMarkedUp = a_IsMarked; }

	//Call draw function of piece with surface as parameter
	void DrawPiece(SDL_Surface*);

	//Draw highlight on surface
	void DrawHighlight(SDL_Surface*);
private:
	bool m_isMarkedUp;
	Piece* m_Piece;
	SDL_Surface* m_Highlight;

};

