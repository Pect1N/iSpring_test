#include "Viewr.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

const int WIDTH = 700; //window width
const int HEIGTH = 700; //window heigth
const int AREA_WIDTH = 640;
const int AREA_HEIGTH = 480;
const int MENU_WIDTH = 640;
const int MENU_HEIGTH = 130;
Vector2f MENU_POS_LEFT_UP;
Vector2f MENU_POS_RIGHT_DOWN;
Vector2f AREA_POS_LEFT_UP;
Vector2f AREA_POS_RIGHT_DOWN;

RenderWindow window(VideoMode(WIDTH, HEIGTH), "Game");

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
	case 1:
	{
		image.loadFromFile("Images/Triangle.png");
		break;
	}
	case 2:
	{
		image.loadFromFile("Images/Rectangle.png");
		break;
	}
	case 3:
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
	int move_width = (WIDTH - AREA_WIDTH) / 2;

	window.clear(Color(175, 180, 240));

	RectangleShape area(Vector2f(AREA_WIDTH, AREA_HEIGTH));
	area.move(move_width, move_width + MENU_HEIGTH + 20);
	area.setFillColor(Color::White);
	window.draw(area);

	AREA_POS_LEFT_UP = area.getPosition();
	AREA_POS_RIGHT_DOWN.x = AREA_POS_LEFT_UP.x + AREA_WIDTH;
	AREA_POS_RIGHT_DOWN.y = AREA_POS_LEFT_UP.y + AREA_HEIGTH;

	RectangleShape menu(Vector2f(MENU_WIDTH, MENU_HEIGTH));
	menu.move(move_width, move_width);
	menu.setFillColor(Color::White);
	window.draw(menu);

	MENU_POS_LEFT_UP = menu.getPosition();
	MENU_POS_RIGHT_DOWN.x = MENU_POS_LEFT_UP.x + MENU_WIDTH;
	MENU_POS_RIGHT_DOWN.y = MENU_POS_LEFT_UP.y + MENU_HEIGTH;

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

int Menu_Click_Check()
{
	Vector2i pixelPos = Mouse::getPosition(window);
	int x = pixelPos.x;
	int y = pixelPos.y;
	if (pixelPos.y > AREA_POS_LEFT_UP.y && pixelPos.x > AREA_POS_LEFT_UP.x && pixelPos.y < AREA_POS_RIGHT_DOWN.y && pixelPos.x < AREA_POS_RIGHT_DOWN.x)
	{
		std::cout << "Area clicked" << std::endl;
	}
	else if (pixelPos.y > MENU_POS_LEFT_UP.y && pixelPos.x > MENU_POS_LEFT_UP.x && pixelPos.y < MENU_POS_RIGHT_DOWN.y && pixelPos.x < MENU_POS_RIGHT_DOWN.x)
	{
		std::cout << "Menu clicked" << std::endl;
	}
	else
		std::cout << "Window clicked" << std::endl;

	return 0;
}