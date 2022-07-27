#include <SFML/Graphics.hpp>
#include <vector>
#include "Boid.hpp"

int main()
{

	//code for a game class
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int window_width = desktop.width;
	int window_height = desktop.height;
	sf::RenderWindow window(desktop, "Event Window");
	window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
	window.setFramerateLimit(144);


	int const num_boids = 60;

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
			boids[i].update_physics();
			boids[i].Cohesion(boids, 50, 1);
			boids[i].Alignment(boids, 50, 1);
			boids[i].normalise_velocity(1);
			boids[i].orientation_update();
			boids[i].render(window);
		}


		window.display();

	}

	return 0;

}