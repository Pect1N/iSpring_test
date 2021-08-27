#pragma once

class Figure
{
private:
	Figure* lower;
	Figure* higher;
	int potnts[2][4];
	int size[2];
	int minimal_size[2];
	//texture of figure
public:
	Figure();
	~Figure();
};

Figure* HIGHEST_ELEMENT = 0;