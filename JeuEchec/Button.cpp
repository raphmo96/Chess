#include "Button.h"
#include "Coordinates.h"


Button::Button(SDL_Surface* a_Image, SDL_Rect* a_Rect, Enums::ButtonType a_Type) :
	m_Image(a_Image),
	m_Rect(a_Rect),
	m_Type(a_Type)
{
}

Button::~Button()
{
	SDL_FreeSurface(m_Image);
	m_Image = NULL;
	delete m_Rect;
}

bool Button::Contains(Coordinates m_Pos) {
	return m_Pos.m_X > m_Rect->x
		&& m_Pos.m_Y > m_Rect->y
		&& m_Pos.m_X < m_Rect->x + m_Rect->w
		&& m_Pos.m_Y < m_Rect->y + m_Rect->h;
}