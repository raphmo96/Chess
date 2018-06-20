#include "Coordinates.h"



Coordinates::Coordinates()
{
	x = 0;
	y = 0;
}

Coordinates::Coordinates(int a_X, int a_Y) :
	x(a_X),
	y(a_Y)
{
}


Coordinates::~Coordinates()
{
}

bool Coordinates::IsInRange(Coordinates a_Start, Coordinates a_End, Coordinates a_Target) {
	return true;
}

Coordinates operator+(Coordinates const & a_A, Coordinates const & a_B)
{
	Coordinates copy(a_A);
	copy.x += a_B.x;
	copy.y += a_B.y;
	return copy;
}

Coordinates operator-(Coordinates const & a_A, Coordinates const & a_B)
{
	Coordinates copy(a_A);
	copy.x -= a_B.x;
	copy.y -= a_B.y;
	return copy;
}

Coordinates operator*(Coordinates const & a_A, int const & a_B)
{
	Coordinates copy(a_A);
	copy.x *= a_B;
	copy.y *= a_B;
	return copy;
}

bool operator==(Coordinates const & a_A, Coordinates const & a_B)
{
	return a_A.x == a_B.x ? a_A.y == a_B.y ? true : false : false;
}
