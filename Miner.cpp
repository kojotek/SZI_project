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
	if (czyWygenerowac) 
	{
		iDraw::drawVector.clear();
		generateNewPopulation();
	}
	
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
		sumaOcen = sumaOcen + obszar[i].ocena;
	}
	Knowledge::wyczyscRejestr(); //czyszczenie rejestru
	
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
	osobnik rodzic1;
	rodzic1.ocena = 0;
	osobnik rodzic2;
	rodzic2.ocena = 0;

	//wybor 2 najlepszych osobnikow do krzyzowania
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (obszar[i].ocena > rodzic1.ocena)
		{
			rodzic2 = rodzic1;
			rodzic1 = obszar[i];
		}
		else if (obszar[i].ocena > rodzic2.ocena) rodzic2 = obszar[i];
	}
	
	Tile * cwiartka1[4][SIZE_X/2][SIZE_Y/2];
	Tile * cwiartka2[4][SIZE_X/2][SIZE_Y/2];

	for (int j = 0; j < SIZE_Y; j++)
	{
		for (int k = 0; k < SIZE_X; k++)
		{
			if (SIZE_X / 2 > k)
			{
				if (SIZE_Y / 2 > j) 
				{ 
					cwiartka1[0][k][j] = rodzic1.genotyp[k][j];
					cwiartka2[0][k][j] = rodzic2.genotyp[k][j];
				}
				else 
				{ 
					cwiartka1[2][k][j % (SIZE_Y / 2)] = rodzic1.genotyp[k][j]; 
					cwiartka2[2][k][j % (SIZE_Y / 2)] = rodzic2.genotyp[k][j];
				}
			}
			else
			{
				if (SIZE_Y / 2 > j) 
				{ 
					cwiartka1[1][k % (SIZE_X / 2)][j] = rodzic1.genotyp[k][j];
					cwiartka2[1][k % (SIZE_X / 2)][j] = rodzic2.genotyp[k][j];
				}
				else 
				{ 
					cwiartka1[3][k % (SIZE_X / 2)][j % (SIZE_Y / 2)] = rodzic1.genotyp[k][j];
					cwiartka2[3][k % (SIZE_X / 2)][j % (SIZE_Y / 2)] = rodzic2.genotyp[k][j];
				}
			}
		}
	}

	//losowanie ciagu bez powtorzen
	int tab1[4];
	int tab2[4];

	for (int n = 0; n < 4; n++)
	{
		bool koniec = false;

		while (!koniec)
		{
			koniec = true;
			int r1 = std::rand() % 4;
			int r2 = std::rand() % 4;

			tab1[n] = r1;
			tab2[n] = r2;

			for (int m = 0; m < n; m++)
			{
				if (tab1[m] == tab1[n]) koniec = false;
				if (tab2[m] == tab2[n]) koniec = false;
			}
		}
	}

	for (int j = 0; j < SIZE_Y; j++)
	{
		for (int k = 0; k < SIZE_X; k++)
		{
			if (SIZE_X / 2 > k)
			{
				if (SIZE_Y / 2 > j) 
				{ 
					rodzic1.genotyp[k][j] = cwiartka2[tab2[0]][k][j];
					rodzic2.genotyp[k][j] = cwiartka1[tab1[0]][k][j];
				}
				else 
				{ 
					rodzic1.genotyp[k][j] = cwiartka2[tab2[2]][k][j % (SIZE_Y / 2)];
					rodzic2.genotyp[k][j] = cwiartka1[tab1[2]][k][j % (SIZE_Y / 2)];
				}
			}
			else
			{
				if (SIZE_Y / 2 > j) 
				{ 
					rodzic1.genotyp[k][j] = cwiartka2[tab2[1]][k % (SIZE_X / 2)][j];
					rodzic2.genotyp[k][j] = cwiartka1[tab1[1]][k % (SIZE_X / 2)][j];
				}
				else 
				{ 
					rodzic1.genotyp[k][j] = cwiartka2[tab2[3]][k % (SIZE_X / 2)][j % (SIZE_Y / 2)];
					rodzic2.genotyp[k][j] = cwiartka1[tab1[3]][k % (SIZE_X / 2)][j % (SIZE_Y / 2)];
				}
			}
		}
	}

	osobnik potomek1;
	potomek1 = rodzic1;
	osobnik potomek2;
	potomek2 = rodzic2;
	int a = 0, b = 0;

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (obszar[i].ocena < potomek1.ocena)
		{
			potomek2 = potomek1;
			b = a;
			potomek1 = obszar[i];
			a = i;
		}
		else if (obszar[i].ocena < potomek2.ocena) 
		{ 
			potomek2 = obszar[i];
			b = i;
		}
	}

	obszar[a] = rodzic1;
	obszar[b] = rodzic2;
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