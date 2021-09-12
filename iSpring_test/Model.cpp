#include "Model.h"
#include "Controller.h"

Figure::Figure(int element_type, Figure* highest)
{
	higher = NULL;
	lower = NULL;
	selected = 0;
	minimal_size.x = 0.2;
	minimal_size.y = 0.2;
	size.x = 1;
	size.y = 1;
	position.x = 300;
	position.y = 370;

	switch (element_type)
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

	if (highest != NULL)
	{
		lower = highest;
		highest->set_higher(this);
	}
}

Figure* Figure::get_lower()
{
	return lower;
}

Figure* Figure::get_higher()
{
	return higher;
}

sf::Image Figure::get_image()
{
	return image;
}

void Figure::set_lower(Figure* lower)
{
	this->lower = lower;
}

void Figure::set_higher(Figure* higher)
{
	this->higher = higher;
}

sf::Vector2f Figure::get_position()
{
	return position;
}

void Figure::set_position(sf::Vector2f pos)
{
	position = pos;
}

void Figure::set_select(int number)
{
	selected = number;
}

int Figure::get_select()
{
	return selected;
}

sf::Vector2f Figure::get_size()
{
	return size;
}

void Figure::set_size(sf::Vector2f new_size)
{
	size = new_size;
}

int Figure::minimal_size_check()
{
	if (size.x > minimal_size.x && size.y > minimal_size.y)
		return 1;
	else
		return 0;
}

Figure::~Figure()
{
	
}
