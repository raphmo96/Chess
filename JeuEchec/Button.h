#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Enums.h"
class Board;
class Coordinates;

class Button
{
public:
	Button(SDL_Surface*, SDL_Rect*, Enums::ButtonType);
	~Button();
	//Given a surface, draw button onto surface;
	void Draw(SDL_Surface* a_Window) { SDL_BlitSurface(m_Image, NULL, a_Window, m_Rect); }

	//Given a position, return if position is inside button;
	bool Contains(Coordinates);

	Enums::ButtonType GetType() { return m_Type; }

	//Returns rect of button;
	SDL_Rect* GetRect() { return m_Rect; }


private:
	SDL_Surface * m_Image;
	SDL_Rect* m_Rect;
	Enums::ButtonType m_Type;
};