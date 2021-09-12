#pragma once

#include "Model.h"

Figure* Element_create(int, Figure*);
Figure* Delete_element(Figure*);
int Element_click_check(sf::Vector2i, Figure*);
void Long_press_check(sf::Vector2i, sf::Vector2i, Figure*, sf::Vector2f, sf::Vector2f);
void Scale(sf::Vector2i, sf::Vector2i, Figure*, sf::Vector2f, sf::Vector2f);
void Move(sf::Vector2i, sf::Vector2i, Figure*, sf::Vector2f, sf::Vector2f);
void Minimal_scale_check();