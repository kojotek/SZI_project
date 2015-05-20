#include "stdafx.h"
#include "miner.h"
#include "application.h"
#include "Knowledge.h"
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

void Miner::generateNewPopulation()
{
	czyWygenerowac = false;

	//selekcja obecnej populacji i utworzenie populacji rodzicielskiej
	selection();
	showGenomes(niebezpieczne, "populacja rodzicow: ", 1);

	//generowanie populacji potomnej
	mutationOperator();
	showGenomes(niebezpieczne, "po mutacji:         ", 0);

	crossoverOperator();
	showGenomes(niebezpieczne, "po krzyzowaniu:     ", 0);
	std::cout << std::endl;
	std::cout << std::endl;
}

void Miner::selection()
{
	int sumaOcen1 = 0, sumaOcen2 = 0, i, j;

	//pobranie ocen kazdego osobnika
	for (i = 0; i < POPULATION_SIZE; i++)
	{
		niebezpieczne[i].ocena = Knowledge::countDangerObject(niebezpieczne[i].genotyp);
		sumaOcen1 = sumaOcen1 + niebezpieczne[i].ocena;

		neutralne[i].ocena = Knowledge::countNeutralObject(neutralne[i].genotyp);
		sumaOcen2 = sumaOcen2 + neutralne[i].ocena;
	}

	std::cout << "-----------------------------------------------------------------";
	showGenomes(niebezpieczne, "populacja startowa: ", 1);

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


void Miner::crossoverOperator()
{
	//losujemy ciag kolejnych rodzicow dla obiektow niebezpiecznych bez powtorzen
	int rodzice_a[POPULATION_SIZE];
	std::cout << std::endl;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		bool koniec = false;
		while (!koniec)
		{
			rodzice_a[i] = std::rand() % POPULATION_SIZE;
			koniec = true;

			for (int j = 0; j < i; j++)
			{
				if (rodzice_a[i] == rodzice_a[j]) koniec = false;
			}
		}
		std::cout << rodzice_a[i] << " ";
	}

	//losujemy ciag kolejnych rodzicow dla obiektow neutralnych bez powtorzen
	int rodzice_b[POPULATION_SIZE];
	//std::cout << std::endl;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		bool koniec = false;
		while (!koniec)
		{
			rodzice_b[i] = std::rand() % POPULATION_SIZE;
			koniec = true;

			for (int j = 0; j < i; j++)
			{
				if (rodzice_b[i] == rodzice_b[j]) koniec = false;
			}
		}
		//std::cout << rodzice_b[i] << " ";
	}

	//wybieramy maksymalna ilosc par z populacji
	for (int i = 0; i < POPULATION_SIZE - 1; i = i + 2)
	{
		int rodzic_a = rodzice_a[i];
		int rodzic_b = rodzice_a[i+1];
		int rodzic_c = rodzice_b[i];
		int rodzic_d = rodzice_b[i+1];

		float p_ab = (std::rand() % 100) / 100.0;
		float p_cd = (std::rand() % 100) / 100.0;

		int l_ab = (std::rand() % (CHROMOSOME_LENGTH - 2)) + 1;
		int l_cd = (std::rand() % (CHROMOSOME_LENGTH - 2)) + 1;

		osobnik potomek_a, potomek_b, potomek_c, potomek_d;

		//krzyzowanie wybranych rodzicow obiektow niebezpiecznych zgodnie z prawdopodobienstwem krzyzowania
		if (p_ab < CROSSOVER_RATIO)
		{
			for (int j = 0; j < CHROMOSOME_LENGTH; j++)
			{
				if (j < l_ab)
				{
					potomek_a.genotyp.at(j) = niebezpieczne[rodzic_a].genotyp.at(j);
					potomek_b.genotyp.at(j) = niebezpieczne[rodzic_b].genotyp.at(j);
				}
				else
				{
					potomek_a.genotyp.at(j) = niebezpieczne[rodzic_b].genotyp.at(j);
					potomek_b.genotyp.at(j) = niebezpieczne[rodzic_a].genotyp.at(j);
				}
			}

			//potomkowie zastepuja rodzicow
			niebezpieczne[rodzic_a] = potomek_a;
			niebezpieczne[rodzic_b] = potomek_b;
		}

		//krzyzowanie wybranych rodzicow obiektow neutralnych zgodnie z prawdopodobienstwem krzyzowania
		if (p_cd < CROSSOVER_RATIO)
		{
			for (int j = 0; j < CHROMOSOME_LENGTH; j++)
			{
				if (j < l_cd)
				{
					potomek_c.genotyp.at(j) = neutralne[rodzic_c].genotyp.at(j);
					potomek_d.genotyp.at(j) = neutralne[rodzic_d].genotyp.at(j);
				}
				else
				{
					potomek_c.genotyp.at(j) = neutralne[rodzic_d].genotyp.at(j);
					potomek_d.genotyp.at(j) = neutralne[rodzic_c].genotyp.at(j);
				}
			}

			//potomkowie zastepuja rodzicow
			neutralne[rodzic_c] = potomek_c;
			neutralne[rodzic_d] = potomek_d;
		}
	}
}

void Miner::mutationOperator()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < CHROMOSOME_LENGTH; j++)
		{
			float p1 = (std::rand() % 100) / 100.0;
			float p2 = (std::rand() % 100) / 100.0;

			if (p1 < MUTATION_RATIO) niebezpieczne[i].genotyp.at(j) = !niebezpieczne[i].genotyp.at(j);
			if (p2 < MUTATION_RATIO) neutralne[i].genotyp.at(j) = !neutralne[i].genotyp.at(j);
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

bool Miner::randomBool() 
{
	return std::rand() % 2 == 1;
}