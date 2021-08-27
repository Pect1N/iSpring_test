#include "Viewr.h"

#include <SFML/Graphics.hpp>

int WIDTH = 800; //window width
int HEIGTH = 800; //window heigth

void Show_Menu()
{
	using namespace sf;

	RenderWindow window(VideoMode(WIDTH, HEIGTH), "Game");
	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
	}
}