#include "Boid.hpp"
#include "Avector.hpp"
#include "School.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


//The width and height of the desktop screen - global variables
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;



Boid::Boid()
{

		position = Avector(rand() % window_width, rand() % window_height);
		velocity = Avector((rand() % 20) - 10, (rand() % 20) - 10);
		acceleration = Avector(0,0);
		maxSpeed = 7;
		maxForce = 7;
		perceptionRadius = 60;

		
}

void Boid::render(sf::RenderWindow& wind)
{
	arrow.setPosition(position.x, position.y);
	arrow.setRotation(getAngle(velocity) + 180);
	//float colorValue = ((int)(100 + (velocity.magnitude()) * 20)) % 254;
	//arrow.setFillColor(sf::Color(colorValue, colorValue, colorValue));
	wind.draw(arrow);
}

void Boid::createShape()
{
	float x = 17;
	arrow.setPointCount(4);
	arrow.setPosition(position.x, position.y);
	arrow.setFillColor(sf::Color::Color(60,50,0));
	arrow.setOutlineThickness(1);
	arrow.setOutlineColor(sf::Color::Color(120, 100, 0));
	arrow.setPoint(0, sf::Vector2f(x / 5, 0));
	arrow.setPoint(1, sf::Vector2f(x / 2, 1 * x / 5));
	arrow.setPoint(2, sf::Vector2f(4 * x / 5, 0));
	arrow.setPoint(3, sf::Vector2f(x / 2, x));
	arrow.setOrigin(x / 2, x / 2);
}

void Boid::applyForce(Avector force)
{
	acceleration.addVector(force);
}

void Boid::update(std::vector<Boid> &school)
{
	//adds random nature to the boid
	//Avector force(((rand() % 200) - 100) * 0.01, ((rand() % 200) - 100) * 0.01);
	//applyForce(force);
	applyForce((Cohesion(school)));
	//applyForce(Alighment(school));
	//To make the slow down not as abrupt
	acceleration.limit(maxForce);
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

float Boid::getAngle(Avector v) const
{
	float angle = static_cast<float>(atan2(v.x, -v.y) * 180 / 3.1415926);
	return angle;
}


Avector Boid::Cohesion(std::vector<Boid> &school)
{
	Avector average_position(0, 0);
	int count = 0;

	for (int i = 0; i < school.size(); i++)
	{
		float d = position.distance(school[i].position);
		
		if ((d > 0) && (d < perceptionRadius))
		{
			average_position.addVector(school[i].position);
			count++;
		}
	}

	if (count > 0)
	{
		average_position.mulScalar(1 / count);
		average_position = Avector::subTwoVector(average_position, position);
		return average_position;
	}


	else
	{
		Avector temp(0, 0);
		return temp;
	}

	Avector s(0, 0);
	return s;

}

Avector Boid::Alighment(std::vector<Boid> school)
{
	Avector average_velocity(0, 0);
	int count = 0;

	for (int i = 0; i < school.size(); i++)
	{
		float d = position.distance(school[i].position);

		if ((d > 0) && (d < perceptionRadius))
		{
			average_velocity.addVector(school[i].velocity);
			count++;
		}

		
	}

	if (count > 0)
	{
		average_velocity.mulScalar(1 / count);
		average_velocity.normalise();
		average_velocity.mulScalar(maxSpeed);

		Avector force = Avector::subTwoVector(average_velocity, velocity); // want a force towards the average velocity (visualise with triangle)
		force.limit(maxForce);
		return force;
	}

	else
	{
		Avector temp(0, 0);
		return temp;
	}
}



