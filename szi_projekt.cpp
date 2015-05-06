// szi_projekt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "application.h"
#include "iDraw.h"
#include "gameMap.h"
#include "grassTile.h"
#include "Miner.h"
#include "Saper.h"
#include "Cow.h"

int _tmain(int argc, _TCHAR* argv[])
{

	Miner miner;
	Saper saper;
	Cow* cow = new Cow(application::gameMap.getTileByXY(sf::Vector2i(0, 3)));

	while ( application::window.isOpen())
	{

		sf::Event event;
		while (application::window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				application::window.close();
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
				if (!cow->isFinished()) cow->work();
				else
				{
					application::gameState = STATE_MINER;
					delete cow;
					cow = new Cow(application::gameMap.getTileByXY(sf::Vector2i(0, 3)));
				}
				application::window.setTitle("Krowy probuja przejsc na druga strone...");
				break;
		}


		for (unsigned int a(0); a < iDraw::drawVector.size(); a++)
		{
			iDraw::drawVector[a]->draw();
		}
		cow->draw();	//rozwiazanie tymczasowe

		application::window.display();
	}

	return 0;
}