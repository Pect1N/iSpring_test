#include "Controller.h"
#include "Model.h"

Figure* Element_create(int element_type, Figure* highest)
{
	return new Figure(element_type, highest);
}

Figure* Delete_element(Figure* highest)
{
	Figure* pointer = highest;
	//пробегаем по списку и ищем выделенный элемент
	if (pointer != NULL)
	{
		do
		{
			//если такой есть, то удаляем его
			if (pointer->get_select() == 1)
			{
				if (pointer->get_lower() != NULL && pointer->get_higher() != NULL)
				{
					pointer->get_lower()->set_higher(pointer->get_higher());
					pointer->get_higher()->set_lower(pointer->get_lower());
				}
				else if (pointer->get_lower() == NULL && pointer->get_higher() == NULL)
					highest = NULL;
				else if (pointer->get_lower() == NULL)
					pointer->get_higher()->set_lower(NULL);
				else if (pointer->get_higher() == NULL)
				{
					pointer->get_lower()->set_higher(NULL);
					highest = pointer->get_lower();
				}
				delete pointer;
				break;
			}
			else
				pointer = pointer->get_lower();
		} while (pointer != NULL);
	}
	//если нет, то ничего не делаем
	return highest;
}

int Element_click_check(sf::Vector2i position, Figure* highest)
{
	Figure* pointer = highest;
	int select = 0;
	if (pointer != NULL)
	{
		do
		{
			pointer->set_select(0);
			if (position.x > pointer->get_position().x && 
				position.y > pointer->get_position().y && 
				position.x < pointer->get_position().x + pointer->get_size().x * 100 && 
				position.y < pointer->get_position().y + pointer->get_size().y * 100 && select == 0)
			{
				pointer->set_select(1);
				select = 1;
				printf("Element selected\n");
			}
			pointer = pointer->get_lower();
		} while (pointer != NULL);
	}
	if (select == 1)
		return 1;
	else
		return 0;
}

void Move(sf::Vector2i position, sf::Vector2i startposition, Figure* pointer)
{
	sf::Vector2f pos;
	pos.x = pointer->get_position().x + (startposition.x - position.x); // текущая позиция + разность между концом и началом зажима
	pos.y = pointer->get_position().y + (startposition.y - position.y);
	pointer->set_position(pos);
}

void Scale()
{
	Minimal_scale_check();
}

void Minimal_scale_check()
{

}

void Long_press_check(sf::Vector2i startposition, sf::Vector2i position, Figure* highest)
{
	Figure* pointer = highest;
	if (pointer != NULL)
	{
		do
		{
			if (pointer->get_select() == 1)
				Move(startposition, position, pointer);
			pointer = pointer->get_lower();
		} while (pointer != NULL);
	}
}