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
	
	std::string decission;
	int counter;
	int currentMove;
	bool finished;
	std::vector<int> moves;
	Tile* finishingNode;

public:
	static std::vector<Cow*> allCows;
	bool findingWay;
	sf::CircleShape shape;

	Cow( Tile* tile );
	~Cow();
	void work();
	bool workFinished();
	bool animationStep( Tile* from, Tile* to, int step );
	void draw();

	std::vector<int> reconstructWay();
	Tile* findWay();

};

