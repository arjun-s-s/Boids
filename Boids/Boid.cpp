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
		maxSpeed = 10;
		maxForce = 7;


		cohMul = 2;
		sepMul = 8;
		aliMul = .1;

	
		perceptionRadiusCoh = 100;
		perceptionRadiusSep = 60;
		perceptionRadiusAli = 50;

		
}

void Boid::render(sf::RenderWindow& wind)
{
	arrow.setPosition(position.x, position.y);
	arrow.setRotation(getAngle(velocity) + 180);
	float colorValue = ((int)(0 + (velocity.magnitude()) * 10)) % 254;
	arrow.setFillColor(sf::Color(colorValue, rand() % 255, colorValue));
	wind.draw(arrow);
}

void Boid::createShape()
{
	float x = 1;
	arrow.setPointCount(4);
	arrow.setPosition(position.x, position.y);
	arrow.setFillColor(sf::Color::Color(255,255,255));
	arrow.setOutlineThickness(1);
	arrow.setOutlineColor(sf::Color::Color(255, 255, 255));
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

	Avector force(((rand() % 200) - 100) * 0.01, ((rand() % 200) - 100) * 0.01);
	applyForce(force);

	applyForce(Cohesion(school));
	applyForce(Alighment(school));
	applyForce(Seperation(school));

	acceleration.limit(maxForce);
	acceleration.mulScalar(.35);
	velocity.addVector(acceleration);
	velocity.limit(maxSpeed);

	position.addVector(velocity);

	acceleration.mulScalar(0);
	arrow.setPosition(position.x, position.y);

}

void Boid::windowEdge()
{
	if (position.x < 0) position.x += window_width;
	if (position.y < 0) position.y += window_height;
	if (position.x > window_width) position.x -= window_width;
	if (position.y > window_height) position.y -= window_height;

	//if (position.x < 0) velocity.x *= -1;
	//if (position.y < 0) velocity.y *= -1;
	//if (position.x > window_width) velocity.x *= -1;
	//if (position.y > window_height) velocity.y *= -1;
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
		
		if ((d > 0) && (d < perceptionRadiusCoh))
		{
			average_position.addVector(school[i].position);
			count++;
		}
	}

	if (count > 0)
	{
		average_position.mulScalar(1.001 / count);
		Avector cohForceVector = Avector::subTwoVector(average_position, position);
		cohForceVector.normalise();
		cohForceVector.mulScalar(cohMul);
		return cohForceVector;
	}


	else
	{
		Avector temp(0, 0);
		return temp;
	}

}

Avector Boid::Alighment(std::vector<Boid> &school)
{
	Avector average_velocity(0, 0);
	int count = 0;

	for (int i = 0; i < school.size(); i++)
	{
		float d = position.distance(school[i].position);

		if ((d > 0) && (d < perceptionRadiusAli))
		{
			average_velocity.addVector(school[i].velocity);
			count++;
		}

		
	}

	if (count > 0)
	{
		average_velocity.mulScalar(1.001 / count);
		Avector force = Avector::subTwoVector(average_velocity, velocity); // want a force towards the average velocity (visualise with triangle)
		average_velocity.normalise();
		average_velocity.mulScalar(aliMul);
		return force;
	}

	else
	{
		Avector temp(0, 0);
		return temp;
	}
}

Avector Boid::Seperation(std::vector<Boid> &school)
{
	Avector steer(0, 0);
	int count = 0;

	for (int i = 0; i < school.size(); i++)
	{
		float d = position.distance(school[i].position);

		if ((d > 0) && (d < perceptionRadiusSep))
		{
			Avector diffVector(0, 0);
			diffVector = diffVector.subTwoVector(position, school[i].position);
			diffVector.normalise();
			diffVector.mulScalar(1 / d);
			steer.addVector(diffVector);
			count++;
		}

		
	}

	if (count > 0)
	{
		steer.mulScalar(1.001 / count);
		steer.normalise();
		steer.mulScalar(sepMul);
		return steer;
	}

	else {
		Avector temp(0, 0);
		return temp;
	}

}


