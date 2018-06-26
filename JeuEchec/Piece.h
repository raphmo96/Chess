#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Coordinates;

class Piece
{
public:
	Piece(bool, SDL_Surface*);
	~Piece();

	//Draw image on given surface in given rect;
	void virtual Draw(SDL_Surface*, SDL_Rect*);

	//Return wether the piece if black or white
	bool virtual IsWhite() { return m_IsWhite; };

	//Assert if the piece can move to the given coordinates, given its initial coordinates
	bool virtual CanMove(Coordinates, Coordinates);

	//Return total number of movement the piece did
	int GetNbMove() { return m_NbMove; };

	//Increment number of movement
	void RaiseNbMove() { m_NbMove++; }

	std::string GetName() { return m_Name; }

protected:
	bool m_IsWhite;

	bool m_MixedMovement;

	bool m_CanStackMovement;

	bool m_CanReverseMovement;

	bool m_FirstPlay;

	std::string m_Name;

	int m_NbMove;

	std::vector<Coordinates> m_PossibleMove;
	SDL_Surface* m_Image;
};

