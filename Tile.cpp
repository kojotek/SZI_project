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

std::string Tile::getType()
{
	return type;
}

void Tile::setPossibleType( std::string pt )
{
	possibleType = pt;
}

std::string Tile::getPossibleType()
{
	return possibleType;
}