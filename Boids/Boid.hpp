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
	float perceptionRadius;
	sf::ConvexShape arrow;

	Boid();

	void createShape();
	void render(sf::RenderWindow& wind);

	
	void windowEdge();

	Avector Cohesion(std::vector<Boid> school);
	Avector Alighment(std::vector<Boid> school);

	float getAngle(Avector v) const;
	void applyForce(Avector force);

	

	void update(std::vector<Boid> &school);



};

