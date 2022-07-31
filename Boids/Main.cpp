#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Boid.hpp"

int main()
{
	sf::RenderWindow window;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int window_width = desktop.width;
	int window_height = desktop.height;
	window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);



	Boid boid;


	while (window.isOpen())
	{
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
		}


		//update physics
		window.clear();

		boid.update();
		boid.render(window);
		boid.windowEdge();


		window.display();
	}

	return 0;
}