#include "Button.h"



Button::Button(SDL_Surface* a_Image, SDL_Rect* a_Rect) :
	m_Image(a_Image),
	m_Rect(a_Rect)
{
}


Button::~Button()
{
	SDL_FreeSurface(m_Image);
	m_Image = NULL;
	delete m_Rect;
}
