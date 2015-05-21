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

	bool settingCows = true;

	std::vector<Cow*> cows;

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
				if (cows.size() == 0)
				{
					if (settingCows)
					{
					
						settingCows = false;
						for (size_t i = 0; i < application::gameMap.mapSize.y; i += 2)
						{
							cows.push_back( new Cow( application::gameMap.getTileByXY( sf::Vector2i(0, i) ) ) );
						}
					}
					else
					{
						application::gameState = STATE_MINER;
						settingCows = true;
						break;
					}
					
				}

				for (size_t i = 0; i < cows.size(); i++)
				{
					if (!cows[i]->workFinished())
					{
						cows[i]->work();
					}
					else
					{
						cows.erase(cows.begin()+i);
					}
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

		for (size_t i = 0; i < cows.size(); i++)
		{
			cows[i]->draw();
		}

		application::window.display();
	}

	return 0;
}