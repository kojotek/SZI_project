#include "stdafx.h"
#include "Saper.h"
#include "Tile.h"
#include "Application.h"

Saper::Saper()
{
	workFinished = false;
	counter = 0;
}


void Saper::work()
{
	if (application::gameMap.saveObjectsInFile()) workFinished = true;

	if (workFinished)
	{
		application::gameState = STATE_COWS;
		counter = 0;
		workFinished = false;
	}
}