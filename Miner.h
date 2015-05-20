#pragma once
#include "iWork.h"

#define MUTATION_RATIO 0.05 //szansa mutacji
#define CROSSOVER_RATIO 0.5 //szansa krzyzowania

struct osobnik
{
	std::bitset<CHROMOSOME_LENGTH> genotyp;
	int ocena = 0;
};

class Miner : public iWork
{
private:
	int counter;
	bool czyWygenerowac;

	osobnik niebezpieczne[POPULATION_SIZE]; //populacja min i bomb
	osobnik neutralne[POPULATION_SIZE]; //populacja obiektow otoczenia
	
	void generateNewPopulation();
	void selection();
	void crossoverOperator();
	void mutationOperator();
	void showGenomes(osobnik a[POPULATION_SIZE], std::string title, bool showMore);
	bool randomBool();

public:
	void work();
	Miner();
};

