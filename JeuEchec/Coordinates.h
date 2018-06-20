#pragma once
class Coordinates
{
public:
	Coordinates();
	Coordinates(int, int);
	~Coordinates();
	int x;
	int y;
	bool IsInRange(Coordinates, Coordinates, Coordinates);
};

Coordinates operator+(Coordinates const& a, Coordinates const& b);
Coordinates operator-(Coordinates const& a, Coordinates const& b);
Coordinates operator*(Coordinates const& a, int const& b);
bool operator==(Coordinates const& a, Coordinates const& b);