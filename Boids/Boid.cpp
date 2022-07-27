#include "Boid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


Boid::Boid()
{
		float x = 17;
		position.x = 100;
		position.y = 100;
		maxSpeed = 0.07;
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

void Boid::update()
{


	acceleration.x = ((rand() % 2000) - 1000) * 0.00001;
	acceleration.y = ((rand() % 2000) - 1000) * 0.00001;

	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	velocity.limit(maxSpeed);
	position.x += velocity.x;
	position.y += velocity.y;

	acceleration.x = 0;
	acceleration.y = 0;

	if (position.x < 0)  position.x += 1280;
	if (position.x > 1280) position.x -= 1280;
	if (position.y < 0) position.y += 720;
	if (position.y < 0) position.y -= 720;

	arrow.setPosition(position.x, position.y);

	



}


