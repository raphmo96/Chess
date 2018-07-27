#include "PieceFactory.h"
#include "Coordinates.h"
#include "Piece.h"
#include "Pawn.h"
#include "Tower.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Board.h"

PieceFactory::PieceFactory()
{
}


PieceFactory::~PieceFactory()
{
}

Piece * PieceFactory::CreatePiece(const Enums::PieceType a_PieceType, const bool a_PieceColor, const std::string a_ImagePath, const Coordinates a_Coord)
{
	switch (a_PieceType) {
	case Enums::PieceType::Tower:
		return new Tower(a_PieceColor, IMG_Load((a_ImagePath + (a_PieceColor ? "W" : "B") + "Tower.png").c_str()), a_Coord);
		break;
	case Enums::PieceType::Knight:
		//Knight
		return new Knight(a_PieceColor, IMG_Load((a_ImagePath + (a_PieceColor ? "W" : "B") + "Knight.png").c_str()), a_Coord);
		break;
	case Enums::PieceType::Bishop:
		//bishop
		return new Bishop(a_PieceColor, IMG_Load((a_ImagePath + (a_PieceColor ? "W" : "B") + "Bishop.png").c_str()), a_Coord);
		break;
	case Enums::PieceType::King:
		//King
		return new King(a_PieceColor, IMG_Load((a_ImagePath + (a_PieceColor ? "W" : "B") + "King.png").c_str()), a_Coord);
		break;
	case Enums::PieceType::Queen:
		//Queen
		return new Queen(a_PieceColor, IMG_Load((a_ImagePath + (a_PieceColor ? "W" : "B") + "Queen.png").c_str()), a_Coord);
		break;
	case Enums::PieceType::Pawn:
		return new Pawn(a_PieceColor, IMG_Load((a_ImagePath + (a_PieceColor ? "W" : "B") + "Pawn.png").c_str()), a_Coord);
		break;
	}
	return nullptr;

}

