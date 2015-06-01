#pragma once
#include "GameMap.h"

class application
{
public:
	static sf::RenderWindow window;
	static GameMap gameMap;
	static int gameState;
	static int previousGameState;
	application();
	~application();
};