#include <SFML/Graphics.hpp>
#include <vector>
#include "Boid.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Event Window");
	window.setFramerateLimit(144);

	int const num_boids = 200;
	Boid boid[num_boids];





	std::vector<Boid> boids(num_boids);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

		}

		window.clear();

		for (int i = 0; i < num_boids; i++)
		{
			boid[i].update_physics();
			boid[i].Cohesion(boid, num_boids, 20, 1);
			boid[i].Alignment(boid, num_boids, 20, 1);
			boid[i].normalise_velocity(1);
			boid[i].orientation_update();
			boid[i].render(window);
		}


		window.display();

	}

	return 0;

}