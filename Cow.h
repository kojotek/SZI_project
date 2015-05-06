#pragma once
#include "iWork.h"
#include "iDraw.h"
#include "Tile.h"

#define MOVE_FRAMES 120

class Cow : public iWork, iDraw
{
private:
	bool timeForDecission;
	std::string decission;
	Tile* target;
	Tile* current;
	int counter;
	bool finished;

public:
	sf::CircleShape shape;

	Cow( Tile* tile );
	void work();
	bool isFinished();
	void makeNextStep();
	bool moveAnim();
	void draw();
};

