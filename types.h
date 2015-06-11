#pragma once

#define MOVE_FRAMES 15


#define STATE_MINER 0
#define STATE_SAPER 1
#define STATE_COWS 2
#define STATE_PAUSE 3


#define MUTATION_RATIO 0.05 //szansa mutacji
#define CROSSOVER_RATIO 0.2 //szansa krzyzowania


#define POPULATION_SIZE 6 //wielkosc populacji wycinkow mapy w pojedynczej iteracji
#define SIZE_X 8 //szerokosc wycinka mapy
#define SIZE_Y 10 //wysokosc wycinka mapy
#define DANGER_OBJECT_LIMIT 30 //limit bomb na pojedynczym wycinku mapy
#define NEUTRAL_OBJECT_LIMIT 30 //limit objektow otoczenia na pojedynczym wycinku mapy
#define NUMBER_OF_DANGER_OBJECTS 20 //ilosc rodzajow bomb
#define NUMBER_OF_NEUTRAL_OBJECTS 20 //ilosc rodzajow elementow otoczenia
#define DANGER_OBJECT_PRICE 30 //punkty przyznane bombie ktora wybuchla
#define NEUTRAL_OBJECT_PRICE 1 //punkty przyznane obiektowi neutralnemu ktorego unikaja krowy
#define NUMBER_OF_COWS application::gameMap.mapSize.y //liczba krow podczas pojedynczej iteracji


#define TILE_SIZE 30

#define LEFT	0
#define RIGHT	1
#define UP		2
#define DOWN	3


#define REACTION_NONE 0
#define REACTION_EXPLOSION 1

#define RODZAJ_TRAWA		0
#define RODZAJ_NEUTRALNY	1
#define RODZAJ_MINA			2