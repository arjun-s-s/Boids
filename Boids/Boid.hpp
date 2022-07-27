#pragma once

class Boid
{

	sf::Vector2f position; //(x, y)
	sf::Vector2f velocity; //(v_x, v_y)
	sf::Vector2f acceleration; //(a_x, a_y)
	sf::ConvexShape arrow;


public:

	Boid(float x_position = rand() % 1280, float y_position = rand() % 720, float x_velocity = (0.02 * (rand() % 100)) - 1, float y_velocity = (0.02 * (rand() % 100)) - 1, float x_acceleration = 0.0, float y_acceleration = 0.0)
	{
		position.x = x_position;
		position.y = y_position;
		velocity.x = x_velocity;
		velocity.y = y_velocity;
		acceleration.x = x_acceleration;
		acceleration.y = y_acceleration;


		float x = 17;

		arrow.setPointCount(4);
		arrow.setPosition(position);
		arrow.setFillColor(sf::Color::White);
		arrow.setPoint(0, sf::Vector2f(x / 5, 0));
		arrow.setPoint(1, sf::Vector2f(x / 2, 1 * x / 5));
		arrow.setPoint(2, sf::Vector2f(4 * x / 5, 0));
		arrow.setPoint(3, sf::Vector2f(x / 2, x));
		arrow.setOrigin(x / 2, x / 2);
		//arrow.setRotation(100);

	}

	void render(sf::RenderWindow& wind);
	sf::Vector2f get_position();
	sf::Vector2f get_velocity();
	void update_physics();
	void normalise_velocity(float magnitude_velocity);

	void Seperation(Boid boid[], float num_boids, float perception_radius, float strength);
	void Alignment(std::vector<Boid> boids, float perception_radius, float strength);
	void Cohesion(std::vector<Boid> boids, float perception_radius, float strength);
	void orientation_update();
	float distance(sf::Vector2f position);





};