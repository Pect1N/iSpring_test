#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const int WIDTH = 700; //window width
const int HEIGTH = 700; //window heigth
const float AREA_WIDTH = 640;
const float AREA_HEIGTH = 480;
const float MENU_WIDTH = 640;
const float MENU_HEIGTH = 130;
Vector2f MENU_POS_LEFT_UP;
Vector2f MENU_POS_RIGHT_DOWN;
Vector2f AREA_POS_LEFT_UP;
Vector2f AREA_POS_RIGHT_DOWN;

RenderWindow window(VideoMode(WIDTH, HEIGTH), "Game");

class Figure
{
private:
	Figure* lower;
	Figure* higher;
	int potnts[2][4];
	int size[2];
	int minimal_size[2];
	//texture of figure
public:
	Figure();
	~Figure();
};