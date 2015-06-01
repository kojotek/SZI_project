#include "stdafx.h"
#include "types.h"
#include "Tile.h"
#include "Application.h"

Tile::Tile() : shape(sf::Vector2f(TILE_SIZE-1, TILE_SIZE-1))
{
	f = 0;
	g = 0;
	h = 0;
	parent = NULL;
	whichSonAmI = -1;
	weight = 0;
}


void Tile::draw()
{
	application::window.draw(shape);
}

std::bitset<CHROMOSOME_LENGTH> Tile::getType()
{
	return type;
}

void Tile::setType(std::bitset<CHROMOSOME_LENGTH> t)
{
	type = t;
}

bool Tile::onList(std::vector<Tile*> ls)
{
	std::vector<Tile*>::iterator it = std::find(ls.begin(), ls.end(), this);
	return (it != ls.end());
}