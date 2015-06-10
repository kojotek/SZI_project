#pragma once

#include "types.h"
#include "Tile.h"
#include "Application.h"

struct wpis
{
	wpis(int a, int b, sf::Vector2i coord) //typ, reakcja, koordynaty
	{
		type = a;
		reaction = b;
		coordinates = coord;
	}

	int type;
	int reaction = 0;
	sf::Vector2i coordinates;
};

class Knowledge
{
public:
	static std::vector<wpis> rejestr;
	static void wyczyscRejestr();
	static int getScore(Tile * pole, int n, int x, int y);
};

