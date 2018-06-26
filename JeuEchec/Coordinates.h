#pragma once
class Coordinates
{
public:
	Coordinates();
	Coordinates(int, int);
	~Coordinates();
	int m_X;
	int m_Y;
	float GetMagnitude();
};

Coordinates operator+(Coordinates const& a, Coordinates const& b);
Coordinates operator-(Coordinates const& a, Coordinates const& b);
Coordinates operator*(Coordinates const& a, int const& b);
Coordinates operator/(Coordinates const& a, int const& b);
bool operator>(Coordinates const& a, Coordinates const& b);
bool operator==(Coordinates const& a, Coordinates const& b);