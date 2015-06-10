#pragma once

#include "types.h"
#include "Tile.h"
#include "GrassTile.h"

struct osobnik
{
	osobnik()
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				genotyp[i][j] = new GrassTile();
			}
		}
	}

	Tile * genotyp[SIZE_X][SIZE_Y];
	int ocena = 0;
};

class Miner
{
private:
	int counter;
	bool czyWygenerowac;

	osobnik obszar[POPULATION_SIZE]; //populacja min i bomb

	void generateNewPopulation();
	void selection();
	void crossoverOperator();
	void mutationOperator();
	void showGenomes(osobnik a[POPULATION_SIZE], std::string title, bool showMore);

public:
	void work();
	Miner();
};

