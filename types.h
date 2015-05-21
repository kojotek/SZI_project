#pragma once

#define MOVE_FRAMES 30


#define STATE_MINER 0
#define STATE_SAPER 1
#define STATE_COWS 2
#define STATE_PAUSE 3


#define MUTATION_RATIO 0.05 //szansa mutacji
#define CROSSOVER_RATIO 0.5 //szansa krzyzowania


#define POPULATION_SIZE 5 //wielkosc populacji bomb/obiektow w pojedynczej iteracji
#define CHROMOSOME_LENGTH 6 //ilosc cech ktore posiada kazdy obiekt lub bomba
#define NUMBER_OF_COWS application::gameMap.mapSize.y//liczba krow podczas pojedynczej iteracji


#define TILE_SIZE 30


enum direction{
	LEFT = 0, RIGHT, UP, DOWN
};