#pragma once
#include "Coordinates.h"
#include "Piece.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Enums.h"

class PieceFactory
{
public:
	PieceFactory();
	~PieceFactory();

	static Piece* CreatePiece(const Enums::PieceType a_PieceType, const bool a_PieceColor, const std::string a_ImagePath, const Coordinates a_Coord);
};

