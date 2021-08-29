#include "Viewr.h"

#include <SFML/Graphics.hpp>

using namespace sf;

int WIDTH = 800; //window width
int HEIGTH = 800; //window heigth

RenderWindow window(VideoMode(WIDTH, HEIGTH), "Game");

void Show_Menu()
{

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

void Show_Figure(int figure)
{
	Image image;
	Texture texture;
	Sprite sprite;

	switch (figure)
	{
		case 1 :
		{
			image.loadFromFile("Images/Triangle.png");
			break;
		}
		case 2 :
		{
			image.loadFromFile("Images/Rectangle.png");
			break;
		}
		case 3 :
		{
			image.loadFromFile("Images/Elipse.png");
			break;
		}
		default:
		{
			break;
		}
	}
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(10, 10);
	window.draw(sprite);
}