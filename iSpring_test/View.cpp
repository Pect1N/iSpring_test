#include "Viewr.h"
#include "Controller.h"
#include "Model.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

void Show()
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
		Show_Boards();
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			Menu_Click_Check();
		}
		window.display();
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
	sprite.setPosition(WIDTH / 2 - 50, HEIGTH / 2);
	window.draw(sprite);
}

void Show_Boards()
{
	Image image;
	Texture texture;
	Sprite sprite;
	float move_width = (WIDTH - AREA_WIDTH) / 2;

	window.clear(Color(175, 180, 240));

	RectangleShape area(Vector2f(AREA_WIDTH, AREA_HEIGTH));
	area.move(move_width, move_width + MENU_HEIGTH + 20);
	area.setFillColor(Color::White);
	window.draw(area);

	RectangleShape rectangle(Vector2f(MENU_WIDTH, MENU_HEIGTH));
	rectangle.move(move_width, move_width);
	rectangle.setFillColor(Color::White);
	window.draw(rectangle);

	image.loadFromFile("Images/Triangle.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(move_width + 10, move_width + 10);
	window.draw(sprite);

	image.loadFromFile("Images/Rectangle.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(move_width + 120, move_width + 10);
	window.draw(sprite);

	image.loadFromFile("Images/Elipse.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(move_width + 230, move_width + 10);
	window.draw(sprite);
}