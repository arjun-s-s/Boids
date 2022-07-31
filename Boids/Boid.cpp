#include "Boid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


//The width and height of the desktop screen - global variables
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

Boid::Boid()
{
		float x = 17;
		position = Avector(0, 0);
		velocity = Avector(0, 0);
		acceleration = Avector(0, 0);
		maxSpeed = .1;
		maxForce = 0.5;

		//creating shape
		arrow.setPointCount(4);
		arrow.setPosition(position.x,position.y);
		arrow.setFillColor(sf::Color::White);
		arrow.setPoint(0, sf::Vector2f(x / 5, 0));
		arrow.setPoint(1, sf::Vector2f(x / 2, 1 * x / 5));
		arrow.setPoint(2, sf::Vector2f(4 * x / 5, 0));
		arrow.setPoint(3, sf::Vector2f(x / 2, x));
		arrow.setOrigin(x / 2, x / 2);
}

void Boid::render(sf::RenderWindow& wind)
{
	arrow.setPosition(position.x, position.y);
	wind.draw(arrow);
}

void Boid::applyForce(Avector force)
{
	acceleration.addVector(force);
}

void Boid::update()
{

	Avector force(.2, .3);
	applyForce(force);

	//To make the slow down not as abrupt
	//acceleration.mulScalar(1);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed);
	position.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);

	arrow.setPosition(position.x, position.y);
}

void Boid::windowEdge()
{
	if (position.x < 0) position.x += window_width;
	if (position.y < 0) position.y += window_height;
	if (position.x > window_width) position.x -= window_width;
	if (position.y > window_height) position.y -= window_height;
}

