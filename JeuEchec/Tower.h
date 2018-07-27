#pragma once
#include "Piece.h"
class Tower :
	public Piece
{
public:
	Tower(bool, SDL_Surface*, Coordinates);
	~Tower();
};

