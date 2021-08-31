#include "Controller.h"
#include "Model.h"

Figure* Element_create(int element_type, Figure* highest)
{
	return new Figure(element_type, highest);
}

Figure* Delete_element(Figure* highest)
{
	highest->get_lower()->set_higher(highest->get_higher());
	Figure* pointer = highest;
	pointer = pointer->get_lower();
	delete highest;
	return pointer;
}