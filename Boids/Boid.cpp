#include <SFML/Graphics.hpp>
#include "Boid.hpp"






void Boid::render(sf::RenderWindow& wind)
{
	arrow.setPosition(position);
	wind.draw(arrow);
}

sf::Vector2f Boid::get_position()
{
	return position;
}

sf::Vector2f Boid::get_velocity()
{
	return velocity;
}

void Boid::update_physics()
{
	position.x += velocity.x;
	position.y += velocity.y;
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;


	if (position.x > 1280 && velocity.x > 0) position.x -= 1280;
	else if (position.x < 0 && velocity.x < 0) position.x += 1280;
	if (position.y > 720 && velocity.y > 0) position.y -= 720;
	else if (position.y < 0 && velocity.y < 0) position.y += 720;



}

void Boid::normalise_velocity(float magnitude_velocity)
{
	float mag = this->velocity.x * this->velocity.x;
	mag += this->velocity.y * this->velocity.y;
	mag = 1 / sqrt(mag);
	this->velocity = this->velocity * mag * magnitude_velocity;

}

float Boid::distance(sf::Vector2f position)
{
	float x_distance = this->position.x - position.x;
	float y_distance = this->position.y - position.y;


	return sqrt((x_distance * x_distance) + (y_distance * y_distance));
}

void Boid::orientation_update()
{
	float angle = atan2(velocity.x, -velocity.y) * 180 / 3.1415926
		;

	arrow.setRotation(angle);
}

void Boid::Seperation(Boid boid[], float num_boids, float perception_radius, float strength)
{
	//stuff
}

void Boid::Alignment(std::vector<Boid> boids, float perception_radius, float strength)
{
	sf::Vector2f sum_velocity(0.0f, 0.0f);

	float num_boids = boids.size();

	for (int i = 0; i < boids.size(); i++)
	{
		if (this->position != boids[i].get_position() && boids[i].distance(this->position) < perception_radius) //not sure about 'this->' part. Basically filtering out boids we're comparing to.
		{
			sum_velocity += boids[i].get_velocity();
		}
	}

	sum_velocity *= 1 / num_boids;
	this->acceleration += (sum_velocity - this->velocity) * strength;

}

void Boid::Cohesion(std::vector<Boid> boids, float perception_radius, float strength)
{
	sf::Vector2f sum_positon(0.0f, 0.0f);

	float num_boids = boids.size();

	for (int i = 0; i < boids.size(); i++)
	{
		if (boids[i].distance(this->position) < perception_radius) //not sure about 'this->' part. Basically filtering out boids we're comparing to.
		{
			sum_positon += boids[i].get_position();
		}
	}

	sum_positon *= 1 / num_boids;
	this->acceleration = sum_positon * strength;



}