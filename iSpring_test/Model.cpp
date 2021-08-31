#include "Model.h"
#include "Controller.h"

Figure::Figure(int element_type, Figure* highest)
{
	higher = NULL;
	lower = NULL;
	minimal_size.x = 10;
	minimal_size.y = 10;
	size.x = 100;
	size.y = 100;

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

Figure::~Figure()
{
	if (higher != NULL)
		higher->lower = lower;
	if (lower != NULL)
		lower->higher = higher;
}
