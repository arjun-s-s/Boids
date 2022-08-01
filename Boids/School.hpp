#pragma once
#include "School.hpp"
#include "Boid.hpp"
#include "Avector.hpp"
#include <vector>


class School
{
public:
	std::vector<Boid> school;

	School() {};

	int getSize();
	void addBoid(Boid &boid);
};
