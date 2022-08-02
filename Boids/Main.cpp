#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Boid.hpp"
#include "School.hpp"

int main()
{
	sf::RenderWindow window;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int window_width = desktop.width;
	int window_height = desktop.height;
	window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
	window.setFramerateLimit(60);


	School s;
	int school_size = 300;


	for (int i = 0; i < school_size; i++) {
		Boid boid_temp;
		s.addBoid(boid_temp);
		s.school[i].createShape();
	}


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

		for (int i = 0; i < school_size; i++)
		{
			s.school[i].windowEdge();
			s.school[i].update(s.school);
			s.school[i].render(window);
		}



		window.display();
	}

	return 0;
}