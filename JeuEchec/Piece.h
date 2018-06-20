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

	void virtual Draw(SDL_Surface*, SDL_Rect*);

	bool virtual IsWhite() { return m_IsWhite; };
	bool virtual CanMove(Coordinates, Coordinates);

	int getNbMove() { return m_NbMove; };

protected:
	bool m_IsWhite;

	bool m_MixedMovement;

	bool m_CanStackMovement;

	bool m_CanReverseMovement;

	std::string m_Name;

	int m_NbMove;

	std::vector<Coordinates> m_PossibleMove;
	SDL_Surface* m_Image;
};

