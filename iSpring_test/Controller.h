#pragma once

#include "Model.h"

Figure* Element_create(int, Figure*);
Figure* Delete_element(Figure*);
int Element_click_check(sf::Vector2i, Figure*);
void Long_press_check(sf::Vector2i, sf::Vector2i, Figure*);
void Scale(sf::Vector2i, sf::Vector2i, Figure*);
void Move(sf::Vector2i, sf::Vector2i, Figure*);
void Minimal_scale_check();