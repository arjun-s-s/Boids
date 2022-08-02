#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Avector
{
public:

	float x;
	float y;

	Avector() {
		x = 0;
		y = 0;
	}

	Avector(float xcoord, float ycoord)
	{
		x = xcoord;
		y = ycoord;
	}

	void set(float v, float w);

	void addVector(Avector v);
	void subVector(Avector v);
	static Avector subTwoVector(Avector v1, Avector v2);
	float distance(Avector v) const;

	void mulScalar(float mu);

	float magnitude();
	void normalise();
	void limit(float max);

	

};