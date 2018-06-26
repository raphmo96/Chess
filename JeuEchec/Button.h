#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Button
{
public:
	Button(SDL_Surface*, SDL_Rect*);
	~Button();

	void Draw(SDL_Surface* a_Window) { SDL_BlitSurface(m_Image, NULL, a_Window, m_Rect); }
	SDL_Rect* GetRect() { return m_Rect; }
private:
	SDL_Surface * m_Image;
	SDL_Rect* m_Rect;
};

