#include "Viewr.h"
#include "Model.h"
#include "Controller.h"
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
Vector2f TRIANGLE_LEFT_UP;
Vector2f RECTANGLE_LEFT_UP;
Vector2f ELIPSE_LEFT_UP;

Figure* LAST_FOR_PRINT = NULL;

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
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) // добавить условие единичного нажатия
		{
			Menu_Click_Check();
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete)
		{
			std::cout << "Delete pressed" << std::endl;
			LAST_FOR_PRINT = Delete_element(LAST_FOR_PRINT);
		}
		window.clear(Color(175, 180, 240));
		Show_Boards();
		Show_Figures();
		window.display();
	}
}

void Show_Boards()
{
	Image image;
	Texture texture;
	Sprite sprite;
	int move_width = (WIDTH - AREA_WIDTH) / 2;

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
	TRIANGLE_LEFT_UP = sprite.getPosition();

	image.loadFromFile("Images/Rectangle.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(move_width + 220, move_width + 10);
	window.draw(sprite);
	RECTANGLE_LEFT_UP = sprite.getPosition();

	image.loadFromFile("Images/Elipse.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(move_width + 430, move_width + 10);
	window.draw(sprite);
	ELIPSE_LEFT_UP = sprite.getPosition();
}

void Show_Figures()
{
	Texture texture;
	Sprite sprite;
	Figure* pointer = LAST_FOR_PRINT;

	if (pointer != NULL)
	{
		while (pointer->get_lower() != NULL)
		{
			pointer = pointer->get_lower();
		}
		do
		{
			texture.loadFromImage(pointer->get_image());
			sprite.setTexture(texture);
			sprite.setPosition(300, 370);
			window.draw(sprite);
			pointer = pointer->get_higher();
		} while (pointer != NULL);
	}
}

int Menu_Click_Check()
{
	Vector2i pixelPos = Mouse::getPosition(window);
	if (pixelPos.y > AREA_POS_LEFT_UP.y && pixelPos.x > AREA_POS_LEFT_UP.x && pixelPos.y < AREA_POS_RIGHT_DOWN.y && pixelPos.x < AREA_POS_RIGHT_DOWN.x)
	{
		std::cout << "Area clicked" << std::endl;
	}
	else if (pixelPos.y > MENU_POS_LEFT_UP.y && pixelPos.x > MENU_POS_LEFT_UP.x && pixelPos.y < MENU_POS_RIGHT_DOWN.y && pixelPos.x < MENU_POS_RIGHT_DOWN.x)
	{
		if (pixelPos.y > TRIANGLE_LEFT_UP.y && pixelPos.y < TRIANGLE_LEFT_UP.y + 100 && pixelPos.x > TRIANGLE_LEFT_UP.x && pixelPos.x < TRIANGLE_LEFT_UP.x + 100)
		{
			std::cout << "Triangle clicked" << std::endl;
			LAST_FOR_PRINT = Element_create(1, LAST_FOR_PRINT);
		}
		else if (pixelPos.y > RECTANGLE_LEFT_UP.y && pixelPos.y < RECTANGLE_LEFT_UP.y + 100 && pixelPos.x > RECTANGLE_LEFT_UP.x && pixelPos.x < RECTANGLE_LEFT_UP.x + 100)
		{
			std::cout << "Rectangle clicked" << std::endl;
			LAST_FOR_PRINT = Element_create(2, LAST_FOR_PRINT);
		}
		else if (pixelPos.y > ELIPSE_LEFT_UP.y && pixelPos.y < ELIPSE_LEFT_UP.y + 100 && pixelPos.x > ELIPSE_LEFT_UP.x && pixelPos.x < ELIPSE_LEFT_UP.x + 100)
		{
			std::cout << "Elipse clicked" << std::endl;
			LAST_FOR_PRINT = Element_create(3, LAST_FOR_PRINT);
		}
		else
			std::cout << "Menu clicked" << std::endl;
	}
	else
		std::cout << "Window clicked" << std::endl;

	return 0;
}