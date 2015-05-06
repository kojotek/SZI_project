#pragma once
#include "tile.h"

class GameMap
{
private:
	std::vector<Tile*> tiles;

public:
	sf::Vector2i mapSize;
	Tile* getTileByXY(sf::Vector2i vec);
	Tile* getTileByEnum(int index);
	bool setTileByXY(sf::Vector2i vec, Tile* newOne);
	bool setTileByEnum(int index, Tile* newOne);
	sf::Vector2i getTileCoord( Tile* tile );
	GameMap();
	~GameMap();
};
