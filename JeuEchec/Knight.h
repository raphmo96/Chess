#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
public:
	Knight(bool, SDL_Surface*, Coordinates);
	~Knight();

	bool CanMove(Coordinates, Coordinates);
};

