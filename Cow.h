#pragma once
#include "iWork.h"
#include "iDraw.h"
#include "Tile.h"
#include "types.h"

class Cow : public iWork
{
private:
	Tile* startTile;
	Tile* current;
	Tile* next;
	bool findingWay;
	std::string decission;
	int counter;
	int currentMove;
	bool finished;
	std::vector<direction> moves;

public:
	sf::CircleShape shape;

	Cow( Tile* tile );
	void work();
	bool workFinished();
	std::vector<direction> findWay();
	bool animationStep( Tile* from, Tile* to, int step );
	void draw();
};

