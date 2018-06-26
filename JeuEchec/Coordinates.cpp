#include "Coordinates.h"
#include <math.h>


Coordinates::Coordinates()
{
	m_X = 0;
	m_Y = 0;
}

Coordinates::Coordinates(int a_X, int a_Y) :
	m_X(a_X),
	m_Y(a_Y)
{
}

float Coordinates::GetMagnitude() {
	return sqrt(pow(m_X, 2.0f) + pow(m_Y, 2.0f));
}


Coordinates::~Coordinates()
{
}

Coordinates operator+(Coordinates const &a_A, Coordinates const &a_B)
{
	Coordinates copy(a_A);
	copy.m_X += a_B.m_X;
	copy.m_Y += a_B.m_Y;
	return copy;
}

Coordinates operator-(Coordinates const &a_A, Coordinates const &a_B)
{
	Coordinates copy(a_A);
	copy.m_X -= a_B.m_X;
	copy.m_Y -= a_B.m_Y;
	return copy;
}

Coordinates operator*(Coordinates const &a_A, int const &a_B)
{
	Coordinates copy(a_A);
	copy.m_X *= a_B;
	copy.m_Y *= a_B;
	return copy;
}

Coordinates operator/(Coordinates const &a_A, int const &a_B)
{
	Coordinates copy(a_A);
	copy.m_X /= a_B;
	copy.m_Y /= a_B;
	return copy;
}

bool operator>(Coordinates const &a_A, Coordinates const &a_B)
{
	Coordinates copy1(a_A);
	Coordinates copy2(a_B);
	return copy1.GetMagnitude() > copy2.GetMagnitude();
}

bool operator==(Coordinates const &a_A, Coordinates const &a_B)
{
	return a_A.m_X == a_B.m_X ? a_A.m_Y == a_B.m_Y ? true : false : false;
}
