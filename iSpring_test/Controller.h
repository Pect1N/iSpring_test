#pragma once

#include "Model.h"

Figure* Element_create(int, Figure*);
Figure* Delete_element(Figure*);
void Element_click_check(sf::Vector2i, Figure*);