#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
public:
	Knight(bool, SDL_Surface*);
	~Knight();

	bool CanMove(Coordinates, Coordinates);
};

