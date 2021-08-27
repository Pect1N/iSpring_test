#include "Model.h"

Figure::Figure()
{
	if (HIGHEST_ELEMENT != 0)
		lower = HIGHEST_ELEMENT;
	HIGHEST_ELEMENT = this;
}

Figure::~Figure()
{
	if (higher != 0)
		higher->lower = lower;
	if (lower != 0)
		lower->higher = higher;
}
