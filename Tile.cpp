#include "stdafx.h"
#include "tile.h"
#include "application.h"

Tile::Tile() : shape(sf::Vector2f(TILE_SIZE-1, TILE_SIZE-1))
{
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