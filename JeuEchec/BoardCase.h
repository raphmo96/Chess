#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Coordinates;
class Piece;

class BoardCase
{
public:
	BoardCase(SDL_Rect*, SDL_Surface*, SDL_Surface*);
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

	//Assert is marked
	bool GetIsTarget() { return m_IsTarget; }

	//Set mark
	void SetIsTarget(bool a_IsMarked) { m_IsTarget = a_IsMarked; }

	//Call draw function of piece with surface as parameter
	void DrawPiece(SDL_Surface*);

	//Draw highlight on surface
	void DrawHighlight(SDL_Surface*);

	void ChangeHighlight(SDL_Surface* a_New) { m_Highlight = a_New; };
private:
	bool m_isMarkedUp;
	bool m_IsTarget;
	Piece* m_Piece;
	SDL_Surface* m_Highlight;
	SDL_Surface* m_Markup;
};

