#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct Coordinates {
	int x;
	int y;
};

class Piece
{
public:
	Piece(bool, SDL_Surface*);
	~Piece();
	void virtual Draw(SDL_Surface*, SDL_Rect*);
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
	SDL_Surface* m_Image;
};

