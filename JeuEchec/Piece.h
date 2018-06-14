#pragma once
#include <string>
#include <vector>
struct Coordinates {
	int x;
	int y;
};

class Piece
{
public:
	Piece(bool);
	~Piece();
	//bool virtual Draw();
	//Coordinates virtual GetPos();
	//bool virtual CanMove();

private:
	bool m_IsWhite;
	bool m_FixedMovement;
	bool m_MixedMovement;
	bool m_CanStackMovement;
	int m_XMovement;
	int m_YMovement;
	std::string m_Name;
	std::vector<Coordinates> m_PossibleMove;
};

