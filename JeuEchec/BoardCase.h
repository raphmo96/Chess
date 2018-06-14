#pragma once
#include "Piece.h"	
class BoardCase
{
public:
	BoardCase();
	~BoardCase();
	Piece* GetPiece() { return m_Piece; };
	void SetPiece(Piece* a_Piece) { m_Piece = a_Piece; };
	void DrawPiece();
private:
	Piece * m_Piece;
	int m_X;
	int m_Y;

};

