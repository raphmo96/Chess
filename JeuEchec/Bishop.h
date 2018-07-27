#pragma once
#include "Piece.h"
class Bishop :
	public Piece
{
public:
	Bishop(bool, SDL_Surface*,Coordinates);
	~Bishop();

	bool ReceiveDamage(int a_Damage);
};

