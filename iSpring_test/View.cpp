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
int SELECT = 0;

Figure* LAST_FOR_PRINT = NULL;

RenderWindow window(VideoMode(WIDTH, HEIGTH), "Game");

void Show()
{
	Event event;
	Vector2i startPos;
	int a = 0, b = 0;

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
			if (a == 0)
			{
				Menu_Click_Check();
				a = 1;
				startPos = Mouse::getPosition(window);
			}
		}
		if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			a = 0;
			if (SELECT == 1)
			{
				Vector2i pixelPos = Mouse::getPosition(window);
				Long_press_check(startPos, pixelPos, LAST_FOR_PRINT, AREA_POS_LEFT_UP, AREA_POS_RIGHT_DOWN);
				SELECT = 0;
			}
			//проверка отжатия за пределами зоны при перетаскивании фигуры
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) // добавить условие единичного нажатия
		{
			if (b == 0)
			{
				std::cout << "Delete pressed" << std::endl;
				LAST_FOR_PRINT = Delete_element(LAST_FOR_PRINT);
				b = 1;
			}
		}
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
			b = 0;
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
	int a = 0;

	if (pointer != NULL)
	{
		while (pointer->get_lower() != NULL)
			pointer = pointer->get_lower();
		do
		{
			++a;
			texture.loadFromImage(pointer->get_image());
			sprite.setTexture(texture);
			sprite.setPosition(pointer->get_position());
			//Potential bug
			sprite.scale(pointer->get_size());
			window.draw(sprite);
			if (pointer->get_select() == 1)
			{
				//рисование прямых для обводки
				VertexArray line(Lines, 2);
				line[0].color = line[1].color = Color::Black;
				line[0].position = pointer->get_position();
				line[1].position = Vector2f(pointer->get_position().x + pointer->get_size().x * 100, pointer->get_position().y);
				window.draw(line);
				line[0].position = pointer->get_position();
				line[1].position = Vector2f(pointer->get_position().x, pointer->get_position().y + pointer->get_size().y * 100);
				window.draw(line);
				line[0].position = Vector2f(pointer->get_position().x + pointer->get_size().x * 100, pointer->get_position().y);
				line[1].position = Vector2f(pointer->get_position().x + pointer->get_size().x * 100, pointer->get_position().y + pointer->get_size().y * 100);
				window.draw(line);
				line[0].position = Vector2f(pointer->get_position().x, pointer->get_position().y + pointer->get_size().y * 100);
				line[1].position = Vector2f(pointer->get_position().x + pointer->get_size().x * 100, pointer->get_position().y + pointer->get_size().y * 100);
				window.draw(line);
			}
			pointer = pointer->get_higher();
		} while (pointer != NULL);
	}
	//std::cout << "Number of elements " << a << std::endl;
}

int Menu_Click_Check()
{
	Vector2i pixelPos = Mouse::getPosition(window);
	if (pixelPos.y > AREA_POS_LEFT_UP.y && pixelPos.x > AREA_POS_LEFT_UP.x && pixelPos.y < AREA_POS_RIGHT_DOWN.y && pixelPos.x < AREA_POS_RIGHT_DOWN.x)
	{
		std::cout << "Area clicked" << std::endl;
		//функция проверки координат для 
		SELECT = Element_click_check(pixelPos, LAST_FOR_PRINT);
		// функция проверки зажатия мыши
		// если продолжается зажимание, то считываем координаты отжатия
		// вычитаем из координат отжатия координаты нажатия и прибавляем к позиции фигуры с selected = 1 (или указатели применяем)
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