#include "Avector.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void Avector::set(float v, float w)
{
	x = v;
	y = w;

}

void Avector::addVector(Avector v)
{
	x += v.x;
	y += v.y;
}

void Avector::subVector(Avector v)
{
	x -= v.x;
	y -= v.y;
}

Avector Avector::subTwoVector(Avector v1, Avector v2) // can this be optimised?
{
	Avector tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;

	return tmp;


}

void Avector::mulScalar(float mu) // can this be optimised?
{
	x *= mu;
	y *= mu;
}

float Avector::magnitude()
{
	return sqrt(x * x + y * y);
}

void Avector::normalise()
{
	x /= magnitude();
	y /= magnitude();
}

void Avector::limit(float max)
{
	float mag = magnitude();

	if (mag > max)
	{
		normalise();
		mulScalar(max);
	}
}

float Avector::distance(Avector v) const
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx * dx + dy * dy);
	return dist;
}