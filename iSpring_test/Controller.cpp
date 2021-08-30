#include "Controller.h"
#include "Model.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int Menu_Click_Check(Vector2f menu_left_up, Vector2f menu_right_down, Vector2f area_left_up, Vector2f area_right_down)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	int a = pixelPos.x;
	int b = pixelPos.y;
	std::cout << "x = " << a << " y = " << b << std::endl;
	return 0;
	// проверка на координаты нажатия и сравнение с глобальными переменными для меню и для рабочей области
}