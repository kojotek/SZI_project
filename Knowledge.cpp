#include "stdafx.h"
#include "Knowledge.h"
#include "types.h"

std::vector<wpis> Knowledge::rejestr;

void Knowledge::wyczyscRejestr()
{
	rejestr.clear();
}

int Knowledge::getScore(Tile * pole, int n, int x, int y)
{
	sf::Vector2i coord;
	coord.x = ((n % 3) * SIZE_X) + x + 1;
	coord.y = ((n / 3) * 10) + y;
	
	for (int i = 0; i < rejestr.size(); i++)
	{
		if (coord == rejestr.at(i).coordinates && pole->rodzaj == 2) return DANGER_OBJECT_PRICE;
		if ((coord == rejestr.at(i).coordinates && pole->rodzaj == 1) || pole->rodzaj == 0) return 0;
	}

	if (pole->rodzaj == 1) return NEUTRAL_OBJECT_PRICE;
	return 0;
}

