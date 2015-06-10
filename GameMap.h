#pragma once

#include "Tile.h"
class Tile;

class GameMap
{
public:
	std::vector<Tile*> tiles;

public:
	sf::Vector2i mapSize;
	Tile* getTileByXY(sf::Vector2i vec);
	Tile* getTileByEnum(int index);
	bool setTileByXY(sf::Vector2i vec, Tile* newOne);
	bool setTileByEnum(int index, Tile* newOne);
	sf::Vector2i getTileCoord( Tile* tile );
	Tile* getTileNeighbour(Tile* tile, int side);
	bool isTileFinishingLine(Tile* tile);
	int getDistanceFromFinish(Tile* tile);
	void clearPathfinding();
	bool saveObjectsInFile();
	std::string intToStr(int n);
	void loadFromFile(std::string path, int type);
	GameMap();
	~GameMap();
};