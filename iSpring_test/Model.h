#pragma once
#include <SFML/Graphics.hpp>

class Figure
{
private:
	Figure* lower;
	Figure* higher;
	sf::Vector2f points;
	sf::Vector2f size;
	sf::Vector2f minimal_size;
	sf::Image image;
public:
	Figure(int, Figure*);
	~Figure();
	Figure* get_lower();
	Figure* get_higher();
	void set_lower(Figure*);
	void set_higher(Figure*);
	sf::Image get_image();
};