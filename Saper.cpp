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
	workFinished = false;

	/*rozpoznawanie min*/
	
	Tile* result = application::gameMap.getTileByEnum(counter);
	
	if (result != NULL)
	{
		//result->setPossibleType("grassTile");
		counter++;
	}
	else
	{
		workFinished = true;
	}
	/*rozpoznawanie min*/


	if (workFinished)
	{
		application::gameState = STATE_COWS;
		counter = 0;
	}
}