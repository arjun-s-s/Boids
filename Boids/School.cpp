#include "School.hpp"

int School::getSize()
{
	int size = school.size();
	return size;
}

void School::addBoid(Boid &boid) { school.push_back(boid); }

