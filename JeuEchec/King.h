#pragma once
#include "Piece.h"
class King :
	public Piece
{
public:
	King(bool, SDL_Surface*,Coordinates);
	~King();
};

