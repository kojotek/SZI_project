#include "stdafx.h"
#include "GameMap.h"
#include "types.h"
#include "Application.h"
#include "GrassTile.h"


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


std::string GameMap::intToStr(int n)
{
	std::string tmp, ret;
	if (n < 0) {
		ret = "-";
		n = -n;
	}
	do {
		tmp += n % 10 + 48;
		n -= n % 10;
	} while (n /= 10);
	for (int i = tmp.size() - 1; i >= 0; i--)
		ret += tmp[i];
	return ret;
}



struct typeDangerous
{
	int type;
	int weight;
};



void GameMap::loadFromFile(std::string path, int neededType)
{
	std::ifstream file(path, std::ifstream::in);
	std::string str;
	std::vector<std::string> words;
	std::vector<typeDangerous> td;

	while (file >> str)
	{
		words.push_back(str);
	}
	file.close();

	for (size_t i = 0; i < words.size(); i++)
	{
		typeDangerous temptd;

		if (i % 2 == 0)
		{
			std::string toRemove(".jpg");
			std::string::size_type siz = words[i].find(toRemove);
			if (siz != std::string::npos) words[i].erase(siz, toRemove.length());
			temptd.type = atoi(words[i].c_str());
		}
		else
		{
			int possibleType = atoi(words[i].c_str());
			switch (possibleType)
			{
				case 0:	temptd.weight = 2000; break;
				case 1:	temptd.weight = 1200; break;
				case 2:	temptd.weight = 500; break;
				case 3:	temptd.weight = 100; break;
			}
			td.push_back(temptd);
		}
	}

	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->rodzaj == neededType)
		{
			for (size_t w = 0; w < td.size(); w++)
			{
				if (td[w].type == tiles[i]->getType())
				{
					tiles[i]->weight += td[w].weight;
					break;
				}
			}
		}
	}

}