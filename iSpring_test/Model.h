#pragma once
#include <SFML/Graphics.hpp>

class Figure
{
private:
	Figure* lower;
	Figure* higher;
	sf::Vector2f size;
	sf::Vector2f minimal_size;
	sf::Image image;
	sf::Vector2f position;
	int selected;
public:
	Figure(int, Figure*);
	~Figure();
	Figure* get_lower();
	Figure* get_higher();
	void set_lower(Figure*);
	void set_higher(Figure*);
	sf::Image get_image();
	void set_position(sf::Vector2f);
	sf::Vector2f get_position();
	void set_select(int);
	int get_select();
	sf::Vector2f get_size();
	void set_size(sf::Vector2f);
	int minimal_size_check();
};