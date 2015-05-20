#pragma once

#include "iDraw.h"
#include <string>
#include "types.h"

class Tile : public iDraw
{
protected:
	std::bitset<CHROMOSOME_LENGTH> type;
	int weight;

public:
	sf::RectangleShape shape;
	void draw();
	std::bitset<CHROMOSOME_LENGTH> getType();
	void setType(std::bitset<CHROMOSOME_LENGTH> t);
	void setWeight(int w);
	int getWeight();
	virtual void interaction() = 0;
	Tile();
};