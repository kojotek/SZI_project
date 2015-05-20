#include "stdafx.h"
#include "application.h"
#include "gameMap.h"

sf::RenderWindow application::window(sf::VideoMode(800, 600), "szi_projekt");
GameMap application::gameMap;
int application::gameState;
int application::previousGameState;

application::application()
{
	gameState = STATE_MINER;
}

application::~application()
{
}