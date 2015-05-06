#include "stdafx.h"
#include "miner.h"
#include "application.h"
#include "grassTile.h"

Miner::Miner()
{
	workFinished = false;
	counter = 0;
}


void Miner::work()
{
	workFinished = false;

	/*rozstawianie min*/
	bool result = application::gameMap.setTileByEnum(counter, new GrassTile());
	counter++;
	/*rozstawianie min*/
	
	if (result == false)
	{
		workFinished = true;
	}

	if (workFinished)
	{
		application::gameState = STATE_SAPER;
		counter = 0;
	}
}