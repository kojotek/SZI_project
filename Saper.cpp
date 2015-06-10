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
	workFinished = true;

	if (workFinished)
	{
		application::gameMap.loadFromFile("folder_objects_best_prediction.txt", RODZAJ_NEUTRALNY);
		application::gameMap.loadFromFile("folder_mine_best_prediction.txt", RODZAJ_MINA);
		application::gameState = STATE_COWS;
		counter = 0;
		workFinished = false;
	}
}