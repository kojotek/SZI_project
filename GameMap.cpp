#include "stdafx.h"
#include "gameMap.h"
#include "grassTile.h"
#include "application.h"
#include "iDraw.h"

GameMap::GameMap()
{
	mapSize.x = application::window.getSize().x / TILE_SIZE;
	mapSize.y = application::window.getSize().y / TILE_SIZE;

	for (int i = 0; i < mapSize.x*mapSize.y; i++)
	{
		tiles.push_back(new GrassTile());
	}

	for (int a(0); a < mapSize.x; a++)
	{
		for (int b(0); b < mapSize.y; b++)
		{
			getTileByXY( sf::Vector2i(a,b) )->shape.setPosition(sf::Vector2f(a*TILE_SIZE, b*TILE_SIZE));
		}
	}

}


GameMap::~GameMap()
{
}


Tile* GameMap::getTileByXY(sf::Vector2i vec)
{
	if (vec.x < 0 || vec.y < 0 || vec.x >= mapSize.x || vec.y >= mapSize.y)
	{
		return NULL;
	}

	return tiles[vec.x + vec.y*mapSize.x];
}


Tile* GameMap::getTileByEnum(int i)
{
	if (i < 0 || i >= tiles.size() )
	{
		return NULL;
	}

	return tiles[i];
}


bool GameMap::setTileByXY(sf::Vector2i vec, Tile* newOne)
{
	if (vec.x < 0 || vec.y < 0 || vec.x >= mapSize.x || vec.y >= mapSize.y)
	{
		return false;
	}

	Tile* temp = tiles[vec.x + vec.y*mapSize.x];
	newOne->shape.setPosition(sf::Vector2f(vec.x*TILE_SIZE, vec.y*TILE_SIZE));
	delete temp;
	tiles[vec.x + vec.y*mapSize.x] = newOne;

	return true;
}


bool GameMap::setTileByEnum(int i, Tile* newOne)
{
	if (i < 0 || i >= tiles.size())
	{
		return false;
	}

	Tile* temp = tiles[i];
	newOne->shape.setPosition(sf::Vector2f( (i % mapSize.x)*TILE_SIZE, (i / mapSize.x)*TILE_SIZE) );
	delete temp;
	tiles[i] = newOne;

	return true;
}


sf::Vector2i GameMap::getTileCoord(Tile* tile)
{
	sf::Vector2i coord(-1,-1);

	for (int a(0); a < mapSize.x; a++)
	{
		for (int b(0); b < mapSize.y; b++)
		{
			
			if (getTileByXY( sf::Vector2i(a,b) ) == tile)
			{
				coord.x = a;
				coord.y = b;
				break;
			}
		}
	}

	return coord;
}
