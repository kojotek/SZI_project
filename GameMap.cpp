#include "stdafx.h"
#include "gameMap.h"
#include "grassTile.h"
#include "application.h"
#include "iDraw.h"
#include "types.h"

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
			Tile* temp = getTileByXY(sf::Vector2i(a, b));
			if ( temp == tile)
			{
				coord.x = a;
				coord.y = b;
				return coord;
			}
		}
	}

	return coord;
}



Tile* GameMap::getTileNeighbour(Tile* tile, int side)
{
	sf::Vector2i tilePos = getTileCoord(tile);
	
	switch (side)
	{
		case LEFT:
			return getTileByXY(tilePos + sf::Vector2i(-1,0));

		case RIGHT:
			return getTileByXY(tilePos + sf::Vector2i(1, 0));

		case UP:
			return getTileByXY(tilePos + sf::Vector2i(0, -1));

		case DOWN:
			return getTileByXY(tilePos + sf::Vector2i(0, 1));

		default:
			return NULL;
	}
}



bool GameMap::isTileFinishingLine(Tile* tile)
{
	sf::Vector2i tilePos = getTileCoord(tile);
	return (tilePos.x == mapSize.x - 1);
}


int GameMap::getDistanceFromFinish(Tile* tile)
{
	return (application::gameMap.mapSize.x - application::gameMap.getTileCoord(tile).x);
}


void GameMap::clearPathfinding()
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i]->f = 0;
		tiles[i]->g = 0;
		tiles[i]->h = 0;
		tiles[i]->parent = NULL;
		tiles[i]->whichSonAmI = -1;
	}
}