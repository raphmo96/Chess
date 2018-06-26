#pragma once
#include "Piece.h"
class Pawn :
	public Piece
{
public:
	Pawn(bool, SDL_Surface*);
	~Pawn();
	bool CanMove(Coordinates, Coordinates);
};

