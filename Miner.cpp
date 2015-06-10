#include "stdafx.h"
#include "Miner.h"
#include "types.h"
#include "DangerTile.h"
#include "GrassTile.h"
#include "NeutralTile.h"
#include "Application.h"
#include "Knowledge.h"

Miner::Miner()
{
	counter = 0;
	czyWygenerowac = false;
	
	//wybranie populacji startowej losowo
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		Tile * nowy;

		for (int j = 0; j < DANGER_OBJECT_LIMIT; j++)//rozkladanie bomb
		{
			int r = (std::rand() % (NUMBER_OF_DANGER_OBJECTS)) + 1;
			nowy = new DangerTile();
			nowy->setType(r);

			while (true)
			{
				int x = std::rand() % SIZE_X;
				int y = std::rand() % SIZE_Y;

				if (obszar[i].genotyp[x][y]->getType() == 0)
				{
					obszar[i].genotyp[x][y] = nowy;
					break;
				}
			}						
		}

		for (int j = 0; j < NEUTRAL_OBJECT_LIMIT; j++)//rozkladanie elementow otoczenia
		{
			int r = (std::rand() % (NUMBER_OF_NEUTRAL_OBJECTS)) + 1;

			nowy = new NeutralTile();
			nowy->setType(r);

			while (true)
			{
				int x = std::rand() % SIZE_X;
				int y = std::rand() % SIZE_Y;

				if (obszar[i].genotyp[x][y]->getType() == 0)
				{
					obszar[i].genotyp[x][y] = nowy;
					break;
				}
			}
		}
	}
}

void Miner::work()
{
	if (czyWygenerowac) generateNewPopulation();
	
	bool result;

	//pierwszy i ostatni rzad pol zostaw wolny
	int x = application::gameMap.mapSize.x;
	int y = application::gameMap.mapSize.y;
	if (counter % x == 0 || counter % x == x - 1) result = application::gameMap.setTileByEnum(counter, new GrassTile());
	else
	{
		int ygrek = counter / x;
		int iks = counter - (ygrek * x);
		int n;

		if (ygrek < SIZE_Y) n = 0;
		else n = 3;

		if (iks >= 9 && iks < 17) n = n + 1;
		if (iks >= 17 && iks < 25) n = n + 2;

		Tile * nowy;
		
		switch (obszar[n].genotyp[(iks - 1) % SIZE_X][ygrek % SIZE_Y]->rodzaj) //kopiowanie do nowej klasy
		{
			case 1:
				nowy = new NeutralTile();
				nowy->setType(obszar[n].genotyp[(iks - 1) % SIZE_X][ygrek % SIZE_Y]->getType());
				break;

			case 2:
				nowy = new DangerTile();
				nowy->setType(obszar[n].genotyp[(iks - 1) % SIZE_X][ygrek % SIZE_Y]->getType());
				break;

			default:
				nowy = new GrassTile();
				nowy->setType(obszar[n].genotyp[(iks - 1) % SIZE_X][ygrek % SIZE_Y]->getType());
				break;
		}

		result = application::gameMap.setTileByEnum(counter, nowy);
	}

	counter++;
	
	if (result == false)
	{
		application::gameState = STATE_SAPER;
		counter = 0;
		czyWygenerowac = true;
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

void Miner::selection()
{
	int sumaOcen = 0;
	//przygotowanie ocen kazdego osobnika
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		obszar[i].ocena = 0;

		for (int j = 0; j < SIZE_Y; j++)
		{
			for (int k = 0; k < SIZE_X; k++)
			{
				int score = Knowledge::getScore(obszar[i].genotyp[k][j], i, k, j);
				obszar[i].ocena = obszar[i].ocena + score;
			}
		}
		std::cout << obszar[i].ocena << " ";
		sumaOcen = sumaOcen + obszar[i].ocena;
	}
	Knowledge::wyczyscRejestr(); //czyszczenie rejestru
	std::cout << std::endl;

	
	//tworzenie populacji rodzicielskiej - metoda ruletki
	osobnik populacjaRodzicielska[POPULATION_SIZE];

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		int a = std::rand() % sumaOcen;

		for (int j = 0; j < POPULATION_SIZE; j++)
		{
			if ((a = a - obszar[j].ocena) < 0)
			{
				populacjaRodzicielska[i] = obszar[j];
				break;
			}
		}
	}

	//podmiana aktualnych populacji na populacje rodzicielskie
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		obszar[i] = populacjaRodzicielska[i];
	}
	
}


void Miner::crossoverOperator()
{
	//wybieramy maksymalna ilosc par z populacji
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		float p = ((std::rand() % 100) + 1) / 100.0;

		//krzyzowanie obszaru polega na podzieleniu obszaru na cwiartki i wymieszanie ich ze soba
		if (p < CROSSOVER_RATIO)
		{
			Tile * cwiartka[4][SIZE_X/2][SIZE_Y/2];

			for (int j = 0; j < SIZE_Y; j++)
			{
				for (int k = 0; k < SIZE_X; k++)
				{
					if (SIZE_X / 2 > k)
					{
						if (SIZE_Y / 2 > j) cwiartka[0][k][j] = obszar[i].genotyp[k][j];
						else cwiartka[2][k][j % (SIZE_Y / 2)] = obszar[i].genotyp[k][j];
					}
					else
					{
						if (SIZE_Y / 2 > j) cwiartka[1][k % (SIZE_X / 2)][j] = obszar[i].genotyp[k][j];
						else cwiartka[3][k % (SIZE_X / 2)][j % (SIZE_Y / 2)] = obszar[i].genotyp[k][j];
					}
				}
			}

			//losowanie ciagu bez powtorzen
			int tab[4];

			for (int n = 0; n < 4; n++)
			{
				bool koniec = false;

				while (!koniec)
				{
					koniec = true;
					int r = std::rand() % 4;

					tab[n] = r;

					for (int m = 0; m < n; m++)
					{
						if (tab[m] == tab[n]) koniec = false;
					}
				}
				std::cout << tab[n] << " ";
			}
			std::cout << std::endl;
		}
	}
}

void Miner::mutationOperator()
{	
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			for (int k = 0; k < SIZE_X; k++)
			{
				float r = ((std::rand() % 100) + 1) / 100.0;

				//w wyniku mutacji dwa pola, o roznym rodzaju, sa zamieniane miejscami
				if (r <= MUTATION_RATIO)
				{
					bool zgodnosc = false;

					while (!zgodnosc)
					{
						int x = std::rand() % SIZE_X;
						int y = std::rand() % SIZE_Y;

						if (obszar[i].genotyp[k][j]->rodzaj != obszar[i].genotyp[x][y]->rodzaj)
						{
							Tile * temp = obszar[i].genotyp[k][j];
							obszar[i].genotyp[k][j] = obszar[i].genotyp[x][y];
							obszar[i].genotyp[x][y] = temp;

							zgodnosc = true;
						}
					}
				}
			}
		}
	}
}

void Miner::showGenomes(osobnik a[POPULATION_SIZE], std::string title , bool showMore)
{
	std::cout << std::endl;
	std::cout << title;
	for (int i = 0; i < POPULATION_SIZE; i++) 
	{ 
		std::cout << a[i].genotyp;
		if (showMore) std::cout << "_" << a[i].ocena;
		std::cout << " ";
	}
}