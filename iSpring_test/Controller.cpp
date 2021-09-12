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

void Long_press_check(sf::Vector2i startposition, sf::Vector2i position, Figure* highest, sf::Vector2f area_left, sf::Vector2f area_right)
{
	Figure* pointer = highest;
	if (pointer != NULL)
	{
		do
		{
			if (pointer->get_select() == 1)
			{
				if (startposition.x > pointer->get_position().x && startposition.x < pointer->get_position().x + 20 ||
					startposition.y > pointer->get_position().y && startposition.y < pointer->get_position().y + 20 ||
					startposition.x < pointer->get_position().x + pointer->get_size().x * 100 && startposition.x > pointer->get_position().x + pointer->get_size().x * 100 - 20 ||
					startposition.y < pointer->get_position().y + pointer->get_size().y * 100 && startposition.y > pointer->get_position().y + pointer->get_size().y * 100 - 20)
					Scale(position, startposition, pointer, area_left, area_right);
				else
					Move(startposition, position, pointer, area_left, area_right);
			}
			pointer = pointer->get_lower();
		} while (pointer != NULL);
	}
}

void Move(sf::Vector2i position, sf::Vector2i startposition, Figure* pointer, sf::Vector2f area_left, sf::Vector2f area_right)
{
	sf::Vector2f pos;
	pos.x = pointer->get_position().x + (startposition.x - position.x); // текущая позиция + разность между концом и началом зажима
	pos.y = pointer->get_position().y + (startposition.y - position.y);
	//проверка на перемещение от размера и скейла
	//если есть проблемы, то ничего не делать
	if (pos.x < area_left.x ||
		pos.y < area_left.y ||
		pos.x + pointer->get_size().x * 100 > area_right.x ||
		pos.y + pointer->get_size().y * 100 > area_right.y)
	{
	}
	//если всё норм, то применяем это
	else
	{
		pointer->set_position(pos);
	}
}

void Scale(sf::Vector2i position, sf::Vector2i startposition, Figure* pointer, sf::Vector2f area_left, sf::Vector2f area_right)
{
	sf::Vector2f scale;
	sf::Vector2f pos;
	//проверка на точку отжатия
	//если за зоной, то ничего не делать
	if (position.x < area_left.x ||
		position.y < area_left.y ||
		position.x > area_right.x ||
		position.y > area_right.y)
	{
	}
	//если всё норм, то выполняем это
	else
	{
		// лево верх
		if (startposition.x > pointer->get_position().x && startposition.x < pointer->get_position().x + 20 &&
			startposition.y > pointer->get_position().y && startposition.y < pointer->get_position().y + 20)
		{
			scale.x = (startposition.x - position.x) / 100.0;
			scale.x += pointer->get_size().x;
			scale.y = (startposition.y - position.y) / 100.0;
			scale.y += pointer->get_size().y;
			Move(startposition, position, pointer, area_left, area_right);
		}
		// лево низ
		else if (startposition.x > pointer->get_position().x && startposition.x < pointer->get_position().x + 20 &&
			startposition.y < pointer->get_position().y + pointer->get_size().y * 100 && startposition.y > pointer->get_position().y + pointer->get_size().y * 100 - 20)
		{
			scale.x = (startposition.x - position.x) / 100.0;
			scale.x += pointer->get_size().x;
			scale.y = (position.y - startposition.y) / 100.0;
			scale.y += pointer->get_size().y;
			pos.x = pointer->get_position().x + (position.x - startposition.x);
			pos.y = pointer->get_position().y;
			pointer->set_position(pos);
		}
		// право верх
		else if (startposition.x < pointer->get_position().x + pointer->get_size().x * 100 && startposition.x > pointer->get_position().x + pointer->get_size().x * 100 - 20 &&
			startposition.y > pointer->get_position().y && startposition.y < pointer->get_position().y + 20)
		{
			scale.x = (position.x - startposition.x) / 100.0;
			scale.x += pointer->get_size().x;
			scale.y = (startposition.y - position.y) / 100.0;
			scale.y += pointer->get_size().y;
			pos.x = pointer->get_position().x;
			pos.y = pointer->get_position().y + (position.y - startposition.y);
			pointer->set_position(pos);
		}
		// право низ
		else if (startposition.x < pointer->get_position().x + pointer->get_size().x * 100 && startposition.x > pointer->get_position().x + pointer->get_size().x * 100 - 20 &&
			startposition.y < pointer->get_position().y + pointer->get_size().y * 100 && startposition.y > pointer->get_position().y + pointer->get_size().y * 100 - 20)
		{
			scale.x = (position.x - startposition.x) / 100.0;
			scale.x += pointer->get_size().x;
			scale.y = (position.y - startposition.y) / 100.0;
			scale.y += pointer->get_size().y;
		}
		else if (startposition.x > pointer->get_position().x && startposition.x < pointer->get_position().x + 20)
		{
			scale.x = (startposition.x - position.x) / 100.0;
			scale.x += pointer->get_size().x;
			scale.y = pointer->get_size().y;
			pos.x = pointer->get_position().x + (position.x - startposition.x);
			pos.y = pointer->get_position().y;
			pointer->set_position(pos);
		}
		else if (startposition.y > pointer->get_position().y && startposition.y < pointer->get_position().y + 20)
		{
			scale.x = pointer->get_size().x;
			scale.y = (startposition.y - position.y) / 100.0;
			scale.y += pointer->get_size().y;
			pos.x = pointer->get_position().x;
			pos.y = pointer->get_position().y + (position.y - startposition.y);
			pointer->set_position(pos);

		}
		else if (startposition.x < pointer->get_position().x + pointer->get_size().x * 100 && startposition.x > pointer->get_position().x + pointer->get_size().x * 100 - 20)
		{
			scale.x = (position.x - startposition.x) / 100.0;
			scale.x += pointer->get_size().x;
			scale.y = pointer->get_size().y;
		}
		else if (startposition.y < pointer->get_position().y + pointer->get_size().y * 100 && startposition.y > pointer->get_position().y + pointer->get_size().y * 100 - 20)
		{
			scale.x = pointer->get_size().x;
			scale.y = (position.y - startposition.y) / 100.0;
			scale.y += pointer->get_size().y;
		}
		if (pointer->minimal_size_check())
			pointer->set_size(scale);
		else
		{
			scale.x = 0.2;
			scale.y = 0.2;
			pointer->set_size(scale);
		}
	}
}