#pragma once

#define STATE_MINER 0
#define STATE_SAPER 1
#define STATE_COWS 2

#include "gameMap.h"

class application
{
public:
	static sf::RenderWindow window;
	static GameMap gameMap;
	static int gameState;
	application();
	~application();
};