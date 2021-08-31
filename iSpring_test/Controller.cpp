#include "Controller.h"
#include "Model.h"

Figure* Element_create(int element_type, Figure* highest)
{
	return new Figure(element_type, highest);
}