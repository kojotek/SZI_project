#include "stdafx.h"
#include "miner.h"
#include "application.h"
#include "grassTile.h"
#include "dangerTile.h"
#include "neutralTile.h"

Miner::Miner()
{
	counter = 0;
	czyWygenerowac = false;

	//CECHY - 0 / 1
	//waga - lekki / ciezki
	//rozmiar - maly / duzy
	//ksztalt - owalny / kanciaty
	//kolor - jasny / ciemny
	//faktura - gladka / chropowata
	//widocznosc - niska / wysoka


	//wybranie populacji startowej
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < CHROMOSOME_LENGTH; j++)
		{
			bool a = randomBool();
			bool b = randomBool();

			niebezpieczne[i].genotyp.at(j) = a;
			neutralne[i].genotyp.at(j) = b;
		}
	}
}

void Miner::work()
{
	if (czyWygenerowac) generateNewPopulation();

	int rodzajPola = std::rand() % 3;
	int numerOsobnika = std::rand() % POPULATION_SIZE;
	bool result;
	Tile * nowy;

	//pierwszy i ostatni rzad pol zostaw wolny
	int x = application::gameMap.mapSize.x;
	if (counter % x == 0 || counter % x == x - 1) rodzajPola = 0;

	//rozstaw 
	switch(rodzajPola)
	{
		case 0:
			result = application::gameMap.setTileByEnum(counter, new GrassTile());
			break;

		case 1:
			nowy = new DangerTile();
			nowy->setType(niebezpieczne[numerOsobnika].genotyp);
			result = application::gameMap.setTileByEnum(counter, nowy);
			break;

		case 2:
			nowy = new NeutralTile();
			nowy->setType(neutralne[numerOsobnika].genotyp);
			result = application::gameMap.setTileByEnum(counter, nowy);
			break;
	}

	counter++;
	
	if (result == false)
	{
		application::gameState = STATE_SAPER;
		counter = 0;
		czyWygenerowac = true;
	}
}

void Miner::crossoverOperator()
{

}

void Miner::mutationOperator()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < CHROMOSOME_LENGTH; j++)
		{
			double p1 = (std::rand() % 100) / 100.0;
			double p2 = (std::rand() % 100) / 100.0;

			if (p1 < MUTATION_RATIO) niebezpieczne[i].genotyp.at(j) = !niebezpieczne[i].genotyp.at(j);
			if (p2 < MUTATION_RATIO) neutralne[i].genotyp.at(j) = !neutralne[i].genotyp.at(j);
		}
	}
}

void Miner::selection()
{
	int sumaOcen1 = 0, sumaOcen2 = 0, i, j;

	//ocena kazdego osobnika - poki co losowa
	for (i = 0; i < POPULATION_SIZE; i++)
	{
		niebezpieczne[i].ocena = std::rand() % NUMBER_OF_COWS;
		sumaOcen1 = sumaOcen1 + niebezpieczne[i].ocena;

		neutralne[i].ocena = std::rand() % NUMBER_OF_COWS;	
		sumaOcen2 = sumaOcen2 + neutralne[i].ocena;
	}

	//tworzenie populacji rodzicielskiej - metoda ruletki
	osobnik populacjaRodzicielska1[POPULATION_SIZE];
	osobnik populacjaRodzicielska2[POPULATION_SIZE];

	for (i = 0; i < POPULATION_SIZE; i++)
	{
		int a = std::rand() % sumaOcen1;
		int b = std::rand() % sumaOcen2;

		//ustalenie populacji rodzicielskiej dla niebezpiecznych obiektow
		for (j = 0; j < POPULATION_SIZE; j++)
		{
			if (sumaOcen1 == 0) 
			{
				populacjaRodzicielska1[i] = niebezpieczne[std::rand() % POPULATION_SIZE];
				break;
			}

			if ((a = a - niebezpieczne[j].ocena) < 0) 
			{ 
				populacjaRodzicielska1[i] = niebezpieczne[j];
				break;
			}			
		}

		//ustalenie populacji rodzicielskiej dla neutralnych obiektow
		for (j = 0; j < POPULATION_SIZE; j++)
		{
			if (sumaOcen2 == 0)
			{
				populacjaRodzicielska2[i] = neutralne[std::rand() % POPULATION_SIZE];
				break;
			}

			if ((b = b - neutralne[j].ocena) < 0)
			{
				populacjaRodzicielska2[i] = neutralne[j];
				break;
			}
		}		
	}

	//podmiana aktualnych populacji na populacje rodzicielskie
	for (i = 0; i < POPULATION_SIZE; i++)
	{
		niebezpieczne[i] = populacjaRodzicielska1[i];
		neutralne[i] = populacjaRodzicielska2[i];
	}
}

void Miner::generateNewPopulation()
{
	czyWygenerowac = false;

	//selekcja obecnej populacji i utworzenie populacji rodzicielskiej
	selection();

	//generowanie populacji potomnej
	mutationOperator();
	crossoverOperator();
}

void Miner::showGenomes(osobnik a[POPULATION_SIZE], bool showMore)
{
	std::cout << std::endl;
	for (int i = 0; i < POPULATION_SIZE; i++) 
	{ 
		std::cout << a[i].genotyp;
		if (showMore) std::cout << "_" << a[i].ocena;
		std::cout << " ";
	}
}

bool Miner::randomBool() 
{
	return std::rand() % 2 == 1;
}