// szi_projekt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "Knowledge.h"
#include "application.h"
#include "iDraw.h"
#include "gameMap.h"
#include "GrassTile.h"
#include "DangerTile.h"
#include "Miner.h"
#include "Saper.h"
#include "Cow.h"
#include "types.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	Miner miner;
	Saper saper;
	Cow* cow = NULL;

	int cowPosition = 0;

	while ( application::window.isOpen())
	{

		sf::Event event;
		while (application::window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				application::window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (application::gameState == STATE_PAUSE) application::gameState = application::previousGameState;
					else
					{
						application::previousGameState = application::gameState;
						application::gameState = STATE_PAUSE;
					}
				}
			}
		}

		application::window.clear(sf::Color::Black);

		switch (application::gameState)
		{
			case STATE_MINER:
				miner.work();
				application::window.setTitle("Miner rozklada elementy otoczenia...");
				break;

			case STATE_SAPER:
				saper.work();
				application::window.setTitle("Saper analizuje pole minowe...");
				break;

			case STATE_COWS:
				if (cow == NULL)
				{
					if (cowPosition < NUMBER_OF_COWS)
					{
						cow = new Cow(application::gameMap.getTileByXY(sf::Vector2i(0, cowPosition)));
					}
					else
					{
						application::gameState = STATE_MINER;
						cowPosition = 0;
						break;
					}
					
				}

				if (!cow->workFinished())
				{
					cow->work();
				}
				else
				{
					cowPosition++;
					delete cow;
					cow = NULL;
				}
				application::window.setTitle("Krowy probuja przejsc na druga strone...");

				break;


			case STATE_PAUSE:
				application::window.setTitle("PAUZA");
				break;

		}


		for (unsigned int a(0); a < iDraw::drawVector.size(); a++)
		{
			iDraw::drawVector[a]->draw();
		}

		if (cow != NULL)
		{
			cow->draw();
		}

		application::window.display();
	}

	return 0;
}