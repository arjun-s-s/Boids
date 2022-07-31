#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Avector.hpp"

class Boid
{
public:
	Avector position;
	Avector velocity;
	Avector acceleration;
	float maxSpeed;
	float maxForce;
	sf::ConvexShape arrow;

	Boid();

	void render(sf::RenderWindow& wind);

	
	void windowEdge();
	void applyForce(Avector force);
	void update();


};