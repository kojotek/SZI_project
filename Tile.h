#pragma once

#include "iDraw.h"
#include <string>

#define TILE_SIZE 30

class Tile : public iDraw
{
protected:
	std::bitset<CHROMOSOME_LENGTH> type;

public:
	sf::RectangleShape shape;
	void draw();
	std::bitset<CHROMOSOME_LENGTH> getType();
	void setType(std::bitset<CHROMOSOME_LENGTH> t);
	virtual void interaction() = 0;
	Tile();
};